using TravelServices.services;
    
namespace TravelClient.client;

public partial class LoginForm : Form
{
    private ITravelServices Service;
    
    public LoginForm(ITravelServices service)
    {
        this.Service = service;
        InitializeComponent();
    }
    
    private void LoginButton_Click(object sender, EventArgs e)
    {
        string username = TxtBoxUsername.Text;
        string password = TxtBoxPassword.Text;
        if (username.Length == 0 || password.Length == 0)
        {
            MessageBox.Show("Please enter username and password");
        }
        else
        {
            try
            {
                var mainForm = new MainForm(Service);
                var agent = Service.login(username, password, mainForm);
                mainForm.SetLoggedAgent(agent);
                mainForm.FormClosed += (s, args) => this.Show();
                ClearTxt();
                this.Hide();
                mainForm.Show();
            }
            catch (ServiceException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }

    private void SignUpButton_Click(object sender, EventArgs e)
    {
        ClearTxt();
        SignUpForm signUpForm = new SignUpForm(Service);
        signUpForm.FormClosed += (s, args) => this.Show();
        this.Hide();
        ClearTxt();
        signUpForm.Show();
    }
    
    private void CancelButton_Click(object sender, EventArgs e)
    {
        Application.Exit();
    }

    private void ClearTxt()
    {
        TxtBoxUsername.Clear();
        TxtBoxPassword.Clear();
    }
}