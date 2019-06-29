#include<stdio.h>
#include <experimental/filesystem>
#include<stdbool.h>
#include<iostream>
#include<string>

#ifdef __cplusplus
extern "C"
{
#endif

#define ZLIB_WINAPI
#include<zlib.h>

#ifdef __cplusplus
}
#endif

#define PACKAGE_VERSION 1;

#ifdef _WIN32
#define EX_PORT __declspec(dllexport)
#else
#define EX_PORT
#endif // _WIN32


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	bool EX_PORT package_pack(const char* pakPath, const char* path, bool isCompress);
	bool EX_PORT package_unPack(const char* pakPath, const char* path);
#ifdef __cplusplus
}
#endif

struct pakInfo
{
	char fileCount[4];
	char version[1];
};

struct fileInfo
{
	char filePath[512];
	char isCompress[1];
	char compressSize[8];
	char fileSize[8];
};

unsigned int readChars(char* ch, int count)
{
	size_t sum = 0;
	for (int i = 0; i < count; i++)
	{
		size_t c = 0;
		if (ch[i] < 0)
		{
			c = 256 + ch[i];
		}
		else
		{
			c = ch[i];
		}
		sum = sum + c * pow(256, i);
	}
	return sum;
}

void writeChars(char *ch,size_t count,size_t num)
{
	for (int i = count - 1; i >= 0; i--)
	{
		--count;
		auto p = pow(256, count);
		ch[i] = (int)(num / p);
		num = (size_t)(num - ch[i] * p);
	}
}

bool packAFile(FILE ** pakFile,const char * indexPath,const char* path,bool isCompress)
{
	struct fileInfo iFile;
	size_t index = 0;
	auto len = strlen(indexPath);
	auto pak = *pakFile;

	memset(&iFile, 0, sizeof(struct fileInfo));

	for (;index < len; index++)
	{
		if (indexPath[index] != path[index])
			break;
	}

	auto pathLen = strlen(path);
	char* pa = new char[pathLen - index+1];
	strncpy(pa, path + index, pathLen - index);
	pa[pathLen - index] = '\0';
	strcpy(iFile.filePath, pa);
	delete[] pa;

	for (int i = 0; i < sizeof(iFile.filePath); i++)
	{
		if (iFile.filePath[i] == '\\')
		{
			iFile.filePath[i] = '/';
		}
	}

	iFile.isCompress[0] = isCompress;

	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		printf("%s file not found!\n", path);
		return false;
	}

	fseek(file, 0, SEEK_END);
	size_t fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);

	writeChars(iFile.fileSize, sizeof(iFile.fileSize), fileLen);

	char* body = new char[fileLen];
	fread(body, sizeof(char), fileLen, file);

	if (isCompress)
	{
		char* buf = NULL;
		auto blen = compressBound(fileLen);
		buf = new char[blen];
		if (buf == NULL)
		{
			printf("Not Enough Memory!\n");
			fclose(file);
			return false;
		}

		if (compress((Bytef*)buf, &blen, (const Bytef*)body, fileLen) != Z_OK)
		{
			printf("compress failed!\n");
			fclose(file);
			return false;
		}

		writeChars(iFile.compressSize, sizeof(iFile.compressSize), blen);
		fwrite(&iFile, sizeof(struct fileInfo), 1, pak);
		fwrite(buf, sizeof(char), blen, pak);
		delete[] buf;
	}
	else
	{
		fwrite(&iFile, sizeof(struct fileInfo), 1, pak);
		fwrite(body, sizeof(char), fileLen, pak);
	}
	
	delete[] body;
	fclose(file);

	return true;
}

bool fetchFiles(FILE ** pakFile,size_t * fileCount,const char * indexPath,const char* path,bool isCompress)
{
	std::string spath = (path);
	for (auto& path : std::experimental::filesystem::directory_iterator(spath))
	{
		if (std::experimental::filesystem::is_directory(path))
		{
			fetchFiles(pakFile, fileCount, indexPath, path.path().string().c_str(), isCompress);
		}
		else if(std::experimental::filesystem::is_regular_file(path))
		{
			if (!packAFile(pakFile, indexPath, path.path().string().c_str(), isCompress))
			{
				return false;
			}
			(*fileCount)++;
		}
	}
	return true;
}

bool EX_PORT package_pack(const char* pakPath, const char* path, bool isCompress)
{
	FILE* pakFile = NULL;
	size_t fileCount = 0;

	struct pakInfo iPak;
	memset(&iPak, 0, sizeof(iPak));
	iPak.version[0] = PACKAGE_VERSION;

	pakFile = fopen(pakPath, "wb");
	if (pakFile == NULL)
	{
		return false;
	}

	fwrite(&iPak, sizeof(struct pakInfo), 1, pakFile);

	if (!fetchFiles(&pakFile, &fileCount,path, path, isCompress))
	{
		fclose(pakFile);
		return false;
	}

	fseek(pakFile, 0, SEEK_SET);
	writeChars(iPak.fileCount, 4, fileCount);
	fwrite(&iPak, sizeof(struct pakInfo), 1, pakFile);

	fclose(pakFile);
	return true;
}

bool unPackV1(FILE * pakFile,const char * path,size_t filesCount)
{
	for (int i = 0; i < filesCount; i++)
	{
		struct fileInfo iFile;
		memset(&iFile, 0, sizeof(struct fileInfo));

		fread(&iFile, sizeof(iFile), 1, pakFile);
		auto fileSize = readChars(iFile.fileSize,sizeof(iFile.fileSize));

		char* buf = new char[fileSize];

		if (iFile.isCompress[0] == (char)true)
		{
			auto fileCompressSize = readChars(iFile.compressSize, sizeof(iFile.compressSize));
			char* zbuf = new char[fileCompressSize];
			if (zbuf == NULL)
			{
				return false;
			}
			fread(zbuf, sizeof(char), fileCompressSize, pakFile);
			
			if (uncompress((Bytef*)buf, (uLongf*)&fileSize, (Bytef*)zbuf, fileCompressSize) != Z_OK)
			{
				delete[] buf;
				delete[] zbuf;
				return false;
			}

			delete[] zbuf;
		}
		else
		{
			fread(buf, sizeof(char), fileSize, pakFile);
		}

		char* pathBuf = new char[strlen(path) + strlen(iFile.filePath) + 1];
		strcpy(pathBuf, path);
		strcat(pathBuf, iFile.filePath);
		pathBuf[strlen(path) + strlen(iFile.filePath)] = '\0';

#ifdef _WIN32
		auto pathLen = strlen(pathBuf);
		for (int i = 0; i < pathLen; i++)
		{
			if (pathBuf[i] == '/')
			{
				pathBuf[i] = '\\';
			}
		}
#endif // __WIN32

#ifdef _WIN32
		auto pathTmpLen = strlen(strrchr(pathBuf, '\\'));
#else
		auto pathTmpLen = strlen(strrchr(pathBuf, '/'));
#endif
		char* dirBuf = new char[strlen(pathBuf) - pathTmpLen + 1];
		strncpy(dirBuf, pathBuf, strlen(pathBuf) - pathTmpLen);
		dirBuf[strlen(pathBuf) - pathTmpLen] = '\0';
		try {
			std::experimental::filesystem::create_directories(dirBuf);
		}
		catch (std::experimental::filesystem::filesystem_error& e) {
			printf("%s\n",e.what());
		}
		delete[] dirBuf;

		FILE* file = fopen(pathBuf, "wb+");
		delete[] pathBuf;
		if (file == NULL)
		{
			return false;
		}

		fwrite(buf, sizeof(char), fileSize, file);
		fclose(file);

		delete[] buf;
	}
	return true;
}

bool EX_PORT package_unPack(const char* pakPath, const char* path)
{
	FILE* pakFile = NULL;
	struct pakInfo iPak;
	pakFile = fopen(pakPath, "rb");
	if (pakFile == NULL)
	{
		return false;
	}

	fread(&iPak, sizeof(struct pakInfo), 1, pakFile);
	
	switch (iPak.version[0])
	{
	case 1:
		unPackV1(pakFile, path, readChars(iPak.fileCount, 4));
		break;
	default:
		fclose(pakFile);
		return false;
	}

	fclose(pakFile);
	return true;
}

int main(void)
{
	bool isCompress = 0;
	int select = 0;
	std::cout << "1:pack" << std::endl;
	std::cout << "2:unpack" << std::endl;
	std::cin >> select;
	if (select != 1 && select != 2)
	{
		return -1;
	}

	std::cout << "pakPath:";
	std::string pakPath;
	std::cin >> pakPath;

	std:: string path;
	std::cout << "Dir Path:";
	std::cin >> path;

	if (select == 1)
	{
		std::cout << "isCompress?:" << std::endl;
		std::cout << "1:Y" << std::endl;
		std::cout << "0:N" << std::endl;

		std::cin >> isCompress;
	}

	std::cout << std::endl;

	if (select == 1)
	{
		package_pack(pakPath.c_str(), path.c_str(), isCompress);
	}
	else if (select == 2)
	{
		package_unPack(pakPath.c_str(), path.c_str());
	}

	system("pause");
}