namespace lab1sgbd
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnUpdate;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.Label lblPrice;
        private System.Windows.Forms.Label lblProductionDate;
        private System.Windows.Forms.Label lblExpirationDate;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.TextBox txtPrice;
        private System.Windows.Forms.DateTimePicker dtpProductionDate;
        private System.Windows.Forms.DateTimePicker dtpExpirationDate;

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
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            btnAdd = new Button();
            btnDelete = new Button();
            btnUpdate = new Button();
            lblName = new Label();
            lblPrice = new Label();
            lblProductionDate = new Label();
            lblExpirationDate = new Label();
            txtName = new TextBox();
            txtPrice = new TextBox();
            dtpProductionDate = new DateTimePicker();
            dtpExpirationDate = new DateTimePicker();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(12, 15);
            dataGridViewParent.Margin = new Padding(3, 4, 3, 4);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.Size = new Size(700, 250);
            dataGridViewParent.TabIndex = 0;
            dataGridViewParent.SelectionChanged += dataGridViewParent_SelectionChanged;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(12, 275);
            dataGridViewChild.Margin = new Padding(3, 4, 3, 4);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.Size = new Size(700, 250);
            dataGridViewChild.TabIndex = 1;
            // 
            // btnAdd
            // 
            btnAdd.Location = new Point(720, 275);
            btnAdd.Margin = new Padding(3, 4, 3, 4);
            btnAdd.Name = "btnAdd";
            btnAdd.Size = new Size(120, 38);
            btnAdd.TabIndex = 2;
            btnAdd.Text = "Adaugă Produs";
            btnAdd.UseVisualStyleBackColor = true;
            btnAdd.Click += btnAdd_Click;
            // 
            // btnDelete
            // 
            btnDelete.Location = new Point(720, 325);
            btnDelete.Margin = new Padding(3, 4, 3, 4);
            btnDelete.Name = "btnDelete";
            btnDelete.Size = new Size(120, 38);
            btnDelete.TabIndex = 3;
            btnDelete.Text = "Șterge Produs";
            btnDelete.UseVisualStyleBackColor = true;
            btnDelete.Click += btnDelete_Click;
            // 
            // btnUpdate
            // 
            btnUpdate.Location = new Point(720, 375);
            btnUpdate.Margin = new Padding(3, 4, 3, 4);
            btnUpdate.Name = "btnUpdate";
            btnUpdate.Size = new Size(120, 38);
            btnUpdate.TabIndex = 4;
            btnUpdate.Text = "Modifică Produs";
            btnUpdate.UseVisualStyleBackColor = true;
            btnUpdate.Click += btnUpdate_Click;
            // 
            // lblName
            // 
            lblName.Location = new Point(720, 25);
            lblName.Name = "lblName";
            lblName.Size = new Size(120, 29);
            lblName.TabIndex = 5;
            lblName.Text = "Nume Produs";
            // 
            // lblPrice
            // 
            lblPrice.Location = new Point(720, 75);
            lblPrice.Name = "lblPrice";
            lblPrice.Size = new Size(120, 29);
            lblPrice.TabIndex = 6;
            lblPrice.Text = "Preț";
            // 
            // lblProductionDate
            // 
            lblProductionDate.Location = new Point(720, 125);
            lblProductionDate.Name = "lblProductionDate";
            lblProductionDate.Size = new Size(120, 32);
            lblProductionDate.TabIndex = 7;
            lblProductionDate.Text = "Data Fabricare";
            // 
            // lblExpirationDate
            // 
            lblExpirationDate.Location = new Point(720, 175);
            lblExpirationDate.Name = "lblExpirationDate";
            lblExpirationDate.Size = new Size(120, 32);
            lblExpirationDate.TabIndex = 8;
            lblExpirationDate.Text = "Data Expirare";
            // 
            // txtName
            // 
            txtName.Location = new Point(846, 22);
            txtName.Margin = new Padding(3, 4, 3, 4);
            txtName.Name = "txtName";
            txtName.Size = new Size(131, 27);
            txtName.TabIndex = 9;
            // 
            // txtPrice
            // 
            txtPrice.Location = new Point(846, 75);
            txtPrice.Margin = new Padding(3, 4, 3, 4);
            txtPrice.Name = "txtPrice";
            txtPrice.Size = new Size(100, 27);
            txtPrice.TabIndex = 10;
            // 
            // dtpProductionDate
            // 
            dtpProductionDate.Location = new Point(846, 125);
            dtpProductionDate.Margin = new Padding(3, 4, 3, 4);
            dtpProductionDate.Name = "dtpProductionDate";
            dtpProductionDate.Size = new Size(200, 27);
            dtpProductionDate.TabIndex = 11;
            // 
            // dtpExpirationDate
            // 
            dtpExpirationDate.Location = new Point(846, 175);
            dtpExpirationDate.Margin = new Padding(3, 4, 3, 4);
            dtpExpirationDate.Name = "dtpExpirationDate";
            dtpExpirationDate.Size = new Size(200, 27);
            dtpExpirationDate.TabIndex = 12;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1111, 562);
            Controls.Add(dataGridViewParent);
            Controls.Add(dataGridViewChild);
            Controls.Add(btnAdd);
            Controls.Add(btnDelete);
            Controls.Add(btnUpdate);
            Controls.Add(lblName);
            Controls.Add(lblPrice);
            Controls.Add(lblProductionDate);
            Controls.Add(lblExpirationDate);
            Controls.Add(txtName);
            Controls.Add(txtPrice);
            Controls.Add(dtpProductionDate);
            Controls.Add(dtpExpirationDate);
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "Magazinul Naturii";
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

    }
}
