using TravelModel.model;
using TravelServices.services;

namespace TravelClient.client;

public partial class SignUpForm : Form
{
    private ITravelServices Service;

    public SignUpForm(ITravelServices service)
    {
        this.Service = service;
        InitializeComponent();
    }

    private void SignUpButton_Click(object sender, EventArgs e)
    {
        string name = TxtBoxName.Text;
        string username = TxtBoxUsername.Text;
        string password = TxtBoxPassword.Text;
        if(name == "" || username == "" || password == "")
        {
            MessageBox.Show("Please fill in all fields.");
            return;
        }
        
        Agent agent = new Agent(name, username, password);
        try
        {
            Service.AddAgent(agent);
            MessageBox.Show("Sign up successful!");
            this.Close();
        } 
        catch (ServiceException ex)
        {
            Service.logoutForSignUp();
            MessageBox.Show(ex.Message);
        }
    }
    
    private void CancelButton_Click(object sender, EventArgs e)
    {
        // Handle cancel logic here
        this.Close();
    }
}
