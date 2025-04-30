using static System.Net.Mime.MediaTypeNames;
using System.Drawing.Printing;
using System.Windows.Forms;
using System.Xml.Linq;
using Font = System.Drawing.Font;

namespace lab2sgbd
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>

        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Label labelMessage;
        private System.Windows.Forms.Label labelParent;
        private System.Windows.Forms.Label labelChild;
        private System.Windows.Forms.Panel panelParent;
        private System.Windows.Forms.Panel panelChild;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnUpdate;
        private System.Windows.Forms.Button btnDelete;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            // Definire culori
            Color verdeDeschis = Color.FromArgb(144, 238, 144);  // LightGreen
            Color verdePastel = Color.FromArgb(204, 255, 204);   // Pastel Green
            Color verdeIntens = Color.FromArgb(0, 100, 0);        // Dark Green
            Color verdeAccent = Color.FromArgb(34, 139, 34);      // Forest Green

            Font fontStandard = new Font("Segoe UI", 10, FontStyle.Regular);

            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            labelParent = new Label();
            labelChild = new Label();
            labelMessage = new Label();
            panelParent = new Panel();
            panelChild = new Panel();
            btnAdd = new Button();
            btnUpdate = new Button();
            btnDelete = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.BackgroundColor = Color.WhiteSmoke;
            dataGridViewParent.BorderStyle = BorderStyle.Fixed3D;
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(41, 74);
            dataGridViewParent.Font = fontStandard;
            dataGridViewParent.GridColor = verdeAccent;
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.RowTemplate.Height = 24;
            dataGridViewParent.Size = new Size(499, 197);
            dataGridViewParent.TabIndex = 0;
            dataGridViewParent.CellClick += dataGridParent_Click;
            // 
            // labelParent
            // 
            labelParent.AutoSize = true;
            labelParent.Location = new Point(41, 25);
            labelParent.Font = new Font("Segoe UI", 12, FontStyle.Bold);
            labelParent.ForeColor = verdeIntens;
            labelParent.Name = "labelParent";
            labelParent.Size = new Size(50, 20);
            labelParent.TabIndex = 1;
            labelParent.Text = "Parent";
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.BackgroundColor = Color.WhiteSmoke;
            dataGridViewChild.BorderStyle = BorderStyle.Fixed3D;
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(40, 392);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewParent.Font = fontStandard;
            dataGridViewParent.GridColor = verdeAccent;
            dataGridViewChild.RowTemplate.Height = 24;
            dataGridViewChild.Size = new Size(500, 206);
            dataGridViewChild.TabIndex = 2;
            dataGridViewChild.CellClick += dataGridChild_Click;
            // 
            // labelChild
            // 
            labelChild.AutoSize = true;
            labelChild.Font = new Font("Segoe UI", 12, FontStyle.Bold);
            labelChild.ForeColor = verdeIntens;
            labelChild.Location = new Point(41, 356);
            labelChild.Name = "labelChild";
            labelChild.Size = new Size(43, 20);
            labelChild.TabIndex = 3;
            labelChild.Text = "Child";
            // 
            // panelParent
            // 
            panelParent.BackColor = verdePastel;
            panelParent.Location = new Point(616, 74);
            panelParent.Name = "panelParent";
            panelParent.Size = new Size(383, 197);
            panelParent.TabIndex = 4;
            // 
            // panelChild
            //
            panelChild.BackColor = verdePastel;
            panelChild.Location = new Point(616, 392);
            panelChild.Name = "panelChild";
            panelChild.Size = new Size(383, 206);
            panelChild.TabIndex = 0;
            // 
            // btnAdd
            // 
            btnAdd.FlatStyle = FlatStyle.Popup;
            btnAdd.Font = fontStandard;
            btnAdd.BackColor = verdeDeschis;
            btnAdd.Location = new Point(1024, 424);
            btnAdd.Name = "btnAdd";
            btnAdd.Size = new Size(113, 40);
            btnAdd.TabIndex = 5;
            btnAdd.Text = "Adaugă";
            btnAdd.UseVisualStyleBackColor = true;
            btnAdd.Click += addButton_Click;
            // 
            // btnUpdate
            // 
            btnUpdate.FlatStyle = FlatStyle.Popup;
            btnUpdate.Location = new Point(1024, 483);
            btnUpdate.Font = fontStandard;
            btnUpdate.BackColor = verdeDeschis;
            btnUpdate.Name = "btnUpdate";
            btnUpdate.Size = new Size(113, 40);
            btnUpdate.TabIndex = 6;
            btnUpdate.Text = "Modifică";
            btnUpdate.UseVisualStyleBackColor = true;
            btnUpdate.Click += updateButton_Click;
            // 
            // btnDelete
            // 
            btnDelete.FlatStyle = FlatStyle.Popup;
            btnDelete.Location = new Point(1024, 547);
            btnDelete.Name = "btnDelete";
            btnDelete.Size = new Size(113, 40);
            btnDelete.TabIndex = 7;
            btnDelete.Text = "Șterge";
            btnDelete.Font = fontStandard;
            btnDelete.BackColor = verdeDeschis;
            btnDelete.UseVisualStyleBackColor = true;
            btnDelete.Click += deleteButton_Click;
            // 
            // labelMessage
            // 
            labelMessage.AutoSize = true;
            labelMessage.Location = new Point(12, 603);
            labelMessage.Font = fontStandard;
            labelMessage.ForeColor = verdeIntens;
            labelMessage.Name = "labelMessage";
            labelMessage.Size = new Size(0, 20);
            labelMessage.TabIndex = 8;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(120F, 120F);
            AutoScaleMode = AutoScaleMode.Dpi;
            ClientSize = new Size(1162, 643);
            Controls.Add(labelMessage);
            Controls.Add(btnDelete);
            Controls.Add(btnUpdate);
            Controls.Add(btnAdd);
            Controls.Add(panelChild);
            Controls.Add(panelParent);
            Controls.Add(labelChild);
            Controls.Add(dataGridViewChild);
            Controls.Add(labelParent);
            Controls.Add(dataGridViewParent);
            Name = "Form1";
            Text = "Magazinul Naturii";
            Load += LoadData;
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }
        #endregion
    }
}