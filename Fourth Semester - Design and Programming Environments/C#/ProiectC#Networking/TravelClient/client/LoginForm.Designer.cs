using System.ComponentModel;
using System.DirectoryServices;

namespace TravelClient.client;

partial class LoginForm
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

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        LabelUsername = new System.Windows.Forms.Label();
        TxtBoxUsername = new System.Windows.Forms.TextBox();
        LabelPassword = new System.Windows.Forms.Label();
        TxtBoxPassword = new System.Windows.Forms.TextBox();
        BtnLogin = new System.Windows.Forms.Button();
        BtnSignUp = new System.Windows.Forms.Button();
        BtnCancel = new System.Windows.Forms.Button();
        LabelTitle = new System.Windows.Forms.Label();
        PanelLogin = new System.Windows.Forms.Panel();
        PanelLogin.SuspendLayout();
        SuspendLayout();
        // 
        // LabelUsername
        // 
        LabelUsername.AutoSize = true;
        LabelUsername.Location = new System.Drawing.Point(150, 110);
        LabelUsername.Name = "LabelUsername";
        LabelUsername.Size = new System.Drawing.Size(78, 20);
        LabelUsername.TabIndex = 1;
        LabelUsername.Text = "Username:";
        // 
        // TxtBoxUsername
        // 
        TxtBoxUsername.Location = new System.Drawing.Point(255, 103);
        TxtBoxUsername.Name = "TxtBoxUsername";
        TxtBoxUsername.Size = new System.Drawing.Size(200, 27);
        TxtBoxUsername.TabIndex = 2;
        // 
        // LabelPassword
        // 
        LabelPassword.AutoSize = true;
        LabelPassword.Location = new System.Drawing.Point(150, 150);
        LabelPassword.Name = "LabelPassword";
        LabelPassword.Size = new System.Drawing.Size(73, 20);
        LabelPassword.TabIndex = 3;
        LabelPassword.Text = "Password:";
        // 
        // TxtBoxPassword
        // 
        TxtBoxPassword.Location = new System.Drawing.Point(255, 150);
        TxtBoxPassword.Name = "TxtBoxPassword";
        TxtBoxPassword.Size = new System.Drawing.Size(200, 27);
        TxtBoxPassword.TabIndex = 4;
        TxtBoxPassword.UseSystemPasswordChar = true;
        // 
        // BtnLogin
        // 
        BtnLogin.Location = new System.Drawing.Point(160, 200);
        BtnLogin.Name = "BtnLogin";
        BtnLogin.Size = new System.Drawing.Size(95, 30);
        BtnLogin.TabIndex = 5;
        BtnLogin.Text = "Log In";
        BtnLogin.UseVisualStyleBackColor = true;
        BtnLogin.Click += LoginButton_Click;
        // 
        // BtnSignUp
        // 
        BtnSignUp.Location = new System.Drawing.Point(271, 200);
        BtnSignUp.Name = "BtnSignUp";
        BtnSignUp.Size = new System.Drawing.Size(95, 30);
        BtnSignUp.TabIndex = 6;
        BtnSignUp.Text = "Sign Up";
        BtnSignUp.UseVisualStyleBackColor = true;
        BtnSignUp.Click += SignUpButton_Click;
        // 
        // BtnCancel
        // 
        BtnCancel.Location = new System.Drawing.Point(389, 200);
        BtnCancel.Name = "BtnCancel";
        BtnCancel.Size = new System.Drawing.Size(95, 30);
        BtnCancel.TabIndex = 7;
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
        LabelTitle.Size = new System.Drawing.Size(324, 29);
        LabelTitle.TabIndex = 8;
        LabelTitle.Text = "Welcome to Travel Agency";
        // 
        // PanelLogin
        // 
        PanelLogin.Controls.Add(LabelTitle);
        PanelLogin.Controls.Add(LabelUsername);
        PanelLogin.Controls.Add(TxtBoxUsername);
        PanelLogin.Controls.Add(LabelPassword);
        PanelLogin.Controls.Add(TxtBoxPassword);
        PanelLogin.Controls.Add(BtnLogin);
        PanelLogin.Controls.Add(BtnSignUp);
        PanelLogin.Controls.Add(BtnCancel);
        PanelLogin.Location = new System.Drawing.Point(20, 37);
        PanelLogin.Name = "PanelLogin";
        PanelLogin.Size = new System.Drawing.Size(622, 299);
        PanelLogin.TabIndex = 9;
        // 
        // LoginForm
        // 
        ClientSize = new System.Drawing.Size(669, 358);
        Controls.Add(PanelLogin);
        Text = "Sign Up Form";
        PanelLogin.ResumeLayout(false);
        PanelLogin.PerformLayout();
        ResumeLayout(false);
    }
    private System.Windows.Forms.Label LabelUsername;
    private System.Windows.Forms.TextBox TxtBoxUsername;
    private System.Windows.Forms.Label LabelPassword;
    private System.Windows.Forms.TextBox TxtBoxPassword;
    private System.Windows.Forms.Button BtnLogin;
    private System.Windows.Forms.Button BtnSignUp;
    private System.Windows.Forms.Button BtnCancel;
    private System.Windows.Forms.Label LabelTitle;
    private System.Windows.Forms.Panel PanelLogin;
    #endregion
}
    