using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace PackageUI
{
    public partial class PackageUI : Form
    {
        [DllImport("Package.dll",CallingConvention = CallingConvention.Cdecl)]
        private extern static bool package_pack(string pakPath, string path, bool isCompress);

        [DllImport("Package.dll",CallingConvention = CallingConvention.Cdecl)]
        private extern static bool package_unPack(string pakPath, string path);

        public PackageUI()
        {
            InitializeComponent();
        }

        private void Pack_Click(object sender, EventArgs e)
        {
            bool isChecked = false;
            if(this.checkBox1.CheckState == CheckState.Checked)
            {
                isChecked = true;
            }

            package_pack(this.sourceLabel.Text, this.currentLabel.Text, isChecked);
        }

        private void SelectSource_Click(object sender, EventArgs e)
        {
            OpenFileDialog path = new OpenFileDialog();
            path.ShowDialog();
            this.sourceLabel.Text=path.FileName;
        }

        private void SelectDir_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            folder.Description = "选择压缩/解压文件夹目录";
            if (folder.ShowDialog() == DialogResult.OK)
            {
                this.currentLabel.Text = folder.SelectedPath;
            }
        }

        private void UnPack_Click(object sender, EventArgs e)
        {
            package_unPack(this.sourceLabel.Text, this.currentLabel.Text);
        }
    }
}
