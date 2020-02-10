namespace FF12Randomizer
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageBasics = new System.Windows.Forms.TabPage();
            this.tabPageOpenWorld = new System.Windows.Forms.TabPage();
            this.tabPageData = new System.Windows.Forms.TabPage();
            this.tabPageFinish = new System.Windows.Forms.TabPage();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.flagInfo1 = new FF12Randomizer.FlagInfo();
            this.tabControl1.SuspendLayout();
            this.tabPageBasics.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPageBasics);
            this.tabControl1.Controls.Add(this.tabPageOpenWorld);
            this.tabControl1.Controls.Add(this.tabPageData);
            this.tabControl1.Controls.Add(this.tabPageFinish);
            this.tabControl1.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.tabControl1.ItemSize = new System.Drawing.Size(40, 100);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(541, 426);
            this.tabControl1.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.tabControl1.TabIndex = 0;
            this.tabControl1.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.tabControl1_DrawItem);
            // 
            // tabPageBasics
            // 
            this.tabPageBasics.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPageBasics.Controls.Add(this.flowLayoutPanel1);
            this.tabPageBasics.Location = new System.Drawing.Point(104, 4);
            this.tabPageBasics.Name = "tabPageBasics";
            this.tabPageBasics.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBasics.Size = new System.Drawing.Size(433, 418);
            this.tabPageBasics.TabIndex = 0;
            this.tabPageBasics.Text = "Basics";
            this.tabPageBasics.UseVisualStyleBackColor = true;
            // 
            // tabPageOpenWorld
            // 
            this.tabPageOpenWorld.AutoScroll = true;
            this.tabPageOpenWorld.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPageOpenWorld.Location = new System.Drawing.Point(104, 4);
            this.tabPageOpenWorld.Name = "tabPageOpenWorld";
            this.tabPageOpenWorld.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageOpenWorld.Size = new System.Drawing.Size(433, 418);
            this.tabPageOpenWorld.TabIndex = 1;
            this.tabPageOpenWorld.Text = "Open World Flags";
            this.tabPageOpenWorld.UseVisualStyleBackColor = true;
            // 
            // tabPageData
            // 
            this.tabPageData.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPageData.Location = new System.Drawing.Point(104, 4);
            this.tabPageData.Name = "tabPageData";
            this.tabPageData.Size = new System.Drawing.Size(433, 418);
            this.tabPageData.TabIndex = 2;
            this.tabPageData.Text = "Data Flags";
            this.tabPageData.UseVisualStyleBackColor = true;
            // 
            // tabPageFinish
            // 
            this.tabPageFinish.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPageFinish.Location = new System.Drawing.Point(104, 4);
            this.tabPageFinish.Name = "tabPageFinish";
            this.tabPageFinish.Size = new System.Drawing.Size(433, 418);
            this.tabPageFinish.TabIndex = 3;
            this.tabPageFinish.Text = "Finish";
            this.tabPageFinish.UseVisualStyleBackColor = true;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(423, 408);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // flagInfo1
            // 
            this.flagInfo1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.flagInfo1.Location = new System.Drawing.Point(559, 12);
            this.flagInfo1.Name = "flagInfo1";
            this.flagInfo1.Size = new System.Drawing.Size(229, 426);
            this.flagInfo1.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.flagInfo1);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tabControl1.ResumeLayout(false);
            this.tabPageBasics.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageBasics;
        private System.Windows.Forms.TabPage tabPageOpenWorld;
        private System.Windows.Forms.TabPage tabPageData;
        private System.Windows.Forms.TabPage tabPageFinish;
        private FlagInfo flagInfo1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
    }
}

