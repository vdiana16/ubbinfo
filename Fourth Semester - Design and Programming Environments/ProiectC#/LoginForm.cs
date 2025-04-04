using TravelAgency.exception;
using TravelAgency.service;

namespace TravelAgency;

public partial class LoginForm : Form
{
    private Service Service;
    
    public LoginForm(Service service)
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
                var agent = Service.SearchAgentByUsername(username, password);
                MainForm mainForm = new MainForm(Service);
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