using System.ComponentModel;

namespace TravelClient.client;
partial class SignUpForm
{
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private IContainer components = null;

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

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        LabelName = new System.Windows.Forms.Label();
        TxtBoxName = new System.Windows.Forms.TextBox();
        LabelUsername = new System.Windows.Forms.Label();
        TxtBoxUsername = new System.Windows.Forms.TextBox();
        LabelPassword = new System.Windows.Forms.Label();
        TxtBoxPassword = new System.Windows.Forms.TextBox();
        BtnSignUp = new System.Windows.Forms.Button();
        BtnCancel = new System.Windows.Forms.Button();
        LabelTitle = new System.Windows.Forms.Label();
        PanelSignUp = new System.Windows.Forms.Panel();
        PanelSignUp.SuspendLayout();
        SuspendLayout();
        // 
        // LabelName
        // 
        LabelName.AutoSize = true;
        LabelName.Location = new System.Drawing.Point(150, 70);
        LabelName.Name = "LabelName";
        LabelName.Size = new System.Drawing.Size(79, 20);
        LabelName.TabIndex = 0;
        LabelName.Text = "Full Name:";
        // 
        // TxtBoxName
        // 
        TxtBoxName.Location = new System.Drawing.Point(255, 63);
        TxtBoxName.Name = "TxtBoxName";
        TxtBoxName.Size = new System.Drawing.Size(200, 27);
        TxtBoxName.TabIndex = 1;
        // 
        // LabelUsername
        // 
        LabelUsername.AutoSize = true;
        LabelUsername.Location = new System.Drawing.Point(150, 110);
        LabelUsername.Name = "LabelUsername";
        LabelUsername.Size = new System.Drawing.Size(78, 20);
        LabelUsername.TabIndex = 2;
        LabelUsername.Text = "Username:";
        // 
        // TxtBoxUsername
        // 
        TxtBoxUsername.Location = new System.Drawing.Point(255, 103);
        TxtBoxUsername.Name = "TxtBoxUsername";
        TxtBoxUsername.Size = new System.Drawing.Size(200, 27);
        TxtBoxUsername.TabIndex = 3;
        // 
        // LabelPassword
        // 
        LabelPassword.AutoSize = true;
        LabelPassword.Location = new System.Drawing.Point(150, 150);
        LabelPassword.Name = "LabelPassword";
        LabelPassword.Size = new System.Drawing.Size(73, 20);
        LabelPassword.TabIndex = 4;
        LabelPassword.Text = "Password:";
        // 
        // TxtBoxPassword
        // 
        TxtBoxPassword.Location = new System.Drawing.Point(255, 150);
        TxtBoxPassword.Name = "TxtBoxPassword";
        TxtBoxPassword.Size = new System.Drawing.Size(200, 27);
        TxtBoxPassword.TabIndex = 5;
        TxtBoxPassword.UseSystemPasswordChar = true;
        // 
        // BtnSignUp
        // 
        BtnSignUp.Location = new System.Drawing.Point(375, 200);
        BtnSignUp.Name = "BtnSignUp";
        BtnSignUp.Size = new System.Drawing.Size(95, 30);
        BtnSignUp.TabIndex = 7;
        BtnSignUp.Text = "Sign Up";
        BtnSignUp.UseVisualStyleBackColor = true;
        BtnSignUp.Click += SignUpButton_Click;
        // 
        // BtnCancel
        // 
        BtnCancel.Location = new System.Drawing.Point(255, 200);
        BtnCancel.Name = "BtnCancel";
        BtnCancel.Size = new System.Drawing.Size(95, 30);
        BtnCancel.TabIndex = 6;
        BtnCancel.Text = "Cancel";
        BtnCancel.UseVisualStyleBackColor = true;
        BtnCancel.Click += CancelButton_Click;
        // 
        // LabelTitle
        // 
        LabelTitle.AutoSize = true;
        LabelTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Bold);
        LabelTitle.Location = new System.Drawing.Point(160, 10);
        LabelTitle.Name = "LabelTitle";
        LabelTitle.Size = new System.Drawing.Size(250, 29);
        LabelTitle.TabIndex = 8;
        LabelTitle.Text = "Create New Account";
        // 
        // PanelSignUp
        // 
        PanelSignUp.Controls.Add(LabelTitle);
        PanelSignUp.Controls.Add(LabelName);
        PanelSignUp.Controls.Add(TxtBoxName);
        PanelSignUp.Controls.Add(LabelUsername);
        PanelSignUp.Controls.Add(TxtBoxUsername);
        PanelSignUp.Controls.Add(LabelPassword);
        PanelSignUp.Controls.Add(TxtBoxPassword);
        PanelSignUp.Controls.Add(BtnCancel);
        PanelSignUp.Controls.Add(BtnSignUp);
        PanelSignUp.Location = new System.Drawing.Point(20, 37);
        PanelSignUp.Name = "PanelSignUp";
        PanelSignUp.Size = new System.Drawing.Size(622, 299);
        PanelSignUp.TabIndex = 9;
        // 
        // SignUpForm
        // 
        ClientSize = new System.Drawing.Size(669, 358);
        Controls.Add(PanelSignUp);
        Text = "Sign Up Form";
        PanelSignUp.ResumeLayout(false);
        PanelSignUp.PerformLayout();
        ResumeLayout(false);
    }

    #region Windows Form Designer generated code

    #endregion
    private System.Windows.Forms.Label LabelName;
    private System.Windows.Forms.TextBox TxtBoxName;
    private System.Windows.Forms.Label LabelUsername;
    private System.Windows.Forms.TextBox TxtBoxUsername;
    private System.Windows.Forms.Label LabelPassword;
    private System.Windows.Forms.TextBox TxtBoxPassword;
    private System.Windows.Forms.Button BtnSignUp;
    private System.Windows.Forms.Button BtnCancel;
    private System.Windows.Forms.Label LabelTitle;
    private System.Windows.Forms.Panel PanelSignUp;
}