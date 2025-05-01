using System.Data;
using TravelModel.model;
using TravelServices.services;

namespace TravelClient.client;
public partial class MainForm : Form, ITravelObserver
{
    private ITravelServices Service;
    private Agent loggedAgent;
    
    public MainForm(ITravelServices service)
    {
        this.Service = service;
        InitializeComponent();
    }   
    
    public void SetLoggedAgent(Agent agent)
    {
        this.loggedAgent = agent;
    }
    
    public void LoadMain(object sender, EventArgs e)
    {
        IEnumerable<Tour> tours = Service.GetAllTours() ?? new List<Tour>(); 
        LoadTours(tours);
        LoadReservations();
    }

    private void LoadTours(IEnumerable<Tour> tours)
    {
        ToursDataGridView.AutoGenerateColumns = true;
        ToursDataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        
        DataTable dataTable = new DataTable();
        dataTable.Columns.Add("Id", typeof(int));
        dataTable.Columns.Add("Destination", typeof(string));
        dataTable.Columns.Add("TransportCompany", typeof(string));
        dataTable.Columns.Add("DepartureDate", typeof(DateTime));
        dataTable.Columns.Add("Price", typeof(decimal));
        dataTable.Columns.Add("NumberOfAvailableSeats", typeof(int));

        foreach (var tour in tours)
        {
            dataTable.Rows.Add(tour.Id, tour.Destination, tour.TransportCompany, tour.DepartureDate, tour.Price, tour.NumberOfAvailableSeats);
        }
        
        ToursDataGridView.DataSource = dataTable;
    }

    private void LoadReservations()
    {
        ReservationsDataGridView.AutoGenerateColumns = true;
        ReservationsDataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        IEnumerable<Reservation> reservations = Service.GetAllReservations() ?? new List<Reservation>();
        DataTable reservationTable = new DataTable();
        reservationTable.Columns.Add("Id", typeof(int));
        reservationTable.Columns.Add("Destination", typeof(string));
        reservationTable.Columns.Add("ClientName", typeof(string));
        reservationTable.Columns.Add("ClientContact", typeof(string));
        reservationTable.Columns.Add("NumberOfReservedSeats", typeof(int));
        
        foreach (var reservation in reservations)
        {
            reservationTable.Rows.Add(reservation.Id, reservation.Tour.Destination, reservation.ClientName, reservation.ClientContact, reservation.NumberOfReservedSeats);
        }
        
        ReservationsDataGridView.DataSource = reservationTable;
    }
    
    private void BookTourButton_Click(object sender, EventArgs e)
    {
        string clientName = TxtBoxClientName.Text;
        string clientContact = TxtBoxClientContact.Text;
        string numberOfSeats = TxtBoxNumberOfSeats.Text;
        if (string.IsNullOrEmpty(clientName) || string.IsNullOrEmpty(clientContact) || string.IsNullOrEmpty(numberOfSeats))
        {
            MessageBox.Show("Please fill in all fields.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        if (!int.TryParse(numberOfSeats, out int seats) || seats <= 0)
        {
            MessageBox.Show("Number of seats must be a positive integer.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        if (ToursDataGridView.SelectedRows.Count == 0)
        {
            MessageBox.Show("Please select a tour.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        DataGridViewRow selectedRow = ToursDataGridView.SelectedRows[0];
        int selectedTourId = Convert.ToInt32(selectedRow.Cells["Id"].Value);
        Tour selectedTour = Service.GetTourById(selectedTourId);
        try
        {
            Reservation reservation = new Reservation(selectedTour, clientName, clientContact, seats);
            Service.AddReservation(reservation);
            MessageBox.Show("Tour reserved successfully!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            IEnumerable<Tour> tours = Service.GetAllTours() ?? new List<Tour>();
            LoadTours(tours);
            LoadReservations();
        }
        catch (ServiceException ex)
        {
            MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
    
    private void ToursDataGridViewSelectionChanged(object sender, EventArgs e)
    {
        if (ToursDataGridView.SelectedRows.Count > 0)
        {
            DataGridViewRow selectedRow = ToursDataGridView.SelectedRows[0];
            int selectedTourId = Convert.ToInt32(selectedRow.Cells["Id"].Value);
            Tour selectedTour = Service.GetTourById(selectedTourId);
            if (selectedTour != null)
            {
                TxtBoxDestination.Text = selectedTour.Destination;
            }
        }
    }

    private void SearchButton_Click(object sender, EventArgs e)
    {
        string destination = TxtBoxDestination.Text;
        
        // Verificare pentru Departure Date
        if (!DateTime.TryParse(DtpDepartureTime.Value.ToString(), out DateTime departureDate))
        {
            MessageBox.Show("Invalid departure date. Please enter a valid date.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        
        // Validare TimeSpan
        if (!TimeSpan.TryParse(TxtBoxStartTime.Text, out TimeSpan startTime))
        {
            MessageBox.Show("Invalid start time format. Please enter a valid time (hh:mm or hh:mm:ss).", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }

        if (!TimeSpan.TryParse(TxtBoxEndTime.Text, out TimeSpan endTime))
        {
            MessageBox.Show("Invalid end time format. Please enter a valid time (hh:mm or hh:mm:ss).", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        
        if (string.IsNullOrEmpty(destination))
        {
            MessageBox.Show("Please enter a destination.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        
        IEnumerable<Tour> tours = Service.GetToursByDestination(destination, departureDate, startTime, endTime);
        LoadTours(tours);
    }

    private void ViewTours_Click(object sender, EventArgs e)
    {
        IEnumerable<Tour> tours = Service.GetAllTours() ?? new List<Tour>();
        LoadTours(tours);
    }

    private void LogOutButton_Click(object sender, EventArgs e)
    {
        Service.logout(loggedAgent);
        this.Close();
    }
    
    public void tourModified(Tour tour)
    {
        this.BeginInvoke((MethodInvoker)delegate
        {
            var tours = Service.GetAllTours().ToList();
            ToursDataGridView.DataSource = tours;
        });
    }
    
    private void ToursDataGridViewCellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
    {
        if (ToursDataGridView.Columns[e.ColumnIndex].Name == "NumberOfAvailableSeats")
        {
            if (e.Value != null && int.TryParse(e.Value.ToString(), out int seats))
            {
                if (seats == 0)
                {
                    e.CellStyle.ForeColor = Color.Red;
                    e.CellStyle.Font = new Font(ToursDataGridView.Font, FontStyle.Bold);
                }
            }
        }
    }
}

    
