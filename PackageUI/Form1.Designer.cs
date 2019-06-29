namespace PackageUI
{
    partial class PackageUI
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pack = new System.Windows.Forms.Button();
            this.unPack = new System.Windows.Forms.Button();
            this.selectSource = new System.Windows.Forms.Button();
            this.selectDir = new System.Windows.Forms.Button();
            this.sourceLabel = new System.Windows.Forms.Label();
            this.currentLabel = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // pack
            // 
            this.pack.Location = new System.Drawing.Point(84, 190);
            this.pack.Name = "pack";
            this.pack.Size = new System.Drawing.Size(75, 23);
            this.pack.TabIndex = 0;
            this.pack.Text = "打包";
            this.pack.UseVisualStyleBackColor = true;
            this.pack.Click += new System.EventHandler(this.Pack_Click);
            // 
            // unPack
            // 
            this.unPack.Location = new System.Drawing.Point(204, 190);
            this.unPack.Name = "unPack";
            this.unPack.Size = new System.Drawing.Size(75, 23);
            this.unPack.TabIndex = 1;
            this.unPack.Text = "解包";
            this.unPack.UseVisualStyleBackColor = true;
            this.unPack.Click += new System.EventHandler(this.UnPack_Click);
            // 
            // selectSource
            // 
            this.selectSource.Location = new System.Drawing.Point(53, 21);
            this.selectSource.Name = "selectSource";
            this.selectSource.Size = new System.Drawing.Size(76, 23);
            this.selectSource.TabIndex = 2;
            this.selectSource.Text = "选择包";
            this.selectSource.UseVisualStyleBackColor = true;
            this.selectSource.Click += new System.EventHandler(this.SelectSource_Click);
            // 
            // selectDir
            // 
            this.selectDir.Location = new System.Drawing.Point(55, 88);
            this.selectDir.Name = "selectDir";
            this.selectDir.Size = new System.Drawing.Size(75, 23);
            this.selectDir.TabIndex = 3;
            this.selectDir.Text = "选择目录";
            this.selectDir.UseVisualStyleBackColor = true;
            this.selectDir.Click += new System.EventHandler(this.SelectDir_Click);
            // 
            // sourceLabel
            // 
            this.sourceLabel.AutoSize = true;
            this.sourceLabel.Location = new System.Drawing.Point(51, 59);
            this.sourceLabel.Name = "sourceLabel";
            this.sourceLabel.Size = new System.Drawing.Size(0, 12);
            this.sourceLabel.TabIndex = 4;
            // 
            // currentLabel
            // 
            this.currentLabel.AutoSize = true;
            this.currentLabel.Location = new System.Drawing.Point(51, 128);
            this.currentLabel.Name = "currentLabel";
            this.currentLabel.Size = new System.Drawing.Size(0, 12);
            this.currentLabel.TabIndex = 5;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(142, 157);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(72, 16);
            this.checkBox1.TabIndex = 6;
            this.checkBox1.Text = "是否压缩";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // PackageUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 261);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.currentLabel);
            this.Controls.Add(this.sourceLabel);
            this.Controls.Add(this.selectDir);
            this.Controls.Add(this.selectSource);
            this.Controls.Add(this.unPack);
            this.Controls.Add(this.pack);
            this.Name = "PackageUI";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button pack;
        private System.Windows.Forms.Button unPack;
        private System.Windows.Forms.Button selectSource;
        private System.Windows.Forms.Button selectDir;
        private System.Windows.Forms.Label sourceLabel;
        private System.Windows.Forms.Label currentLabel;
        private System.Windows.Forms.CheckBox checkBox1;
    }
}

