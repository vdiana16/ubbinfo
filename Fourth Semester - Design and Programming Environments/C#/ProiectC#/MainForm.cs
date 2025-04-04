using System.Data;
using TravelAgency.exception;
using TravelAgency.model;
using TravelAgency.service;

namespace TravelAgency;

public partial class MainForm : Form
{
    private Service Service;
    
    public MainForm(Service service)
    {
        this.Service = service;
        InitializeComponent();
        
        List<Trip> trips = Service.GetAllTrips() ?? new List<Trip>(); 
        LoadTrips(trips);
        LoadReservations();
    }

    private void LoadTrips(List<Trip> trips)
    {
        TripsDataGridView.AutoGenerateColumns = true;
        TripsDataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        
        DataTable dataTable = new DataTable();
        dataTable.Columns.Add("Id", typeof(int));
        dataTable.Columns.Add("Destination", typeof(string));
        dataTable.Columns.Add("TransportCompany", typeof(string));
        dataTable.Columns.Add("DepartureDate", typeof(DateTime));
        dataTable.Columns.Add("Price", typeof(decimal));
        dataTable.Columns.Add("NumberOfAvailableSeats", typeof(int));

        foreach (var trip in trips)
        {
            dataTable.Rows.Add(trip.Id, trip.Destination, trip.TransportCompany, trip.DepartureDate, trip.Price, trip.NumberOfAvailableSeats);
        }
        
        TripsDataGridView.DataSource = dataTable;
    }

    private void LoadReservations()
    {
        ReservationsDataGridView.AutoGenerateColumns = true;
        ReservationsDataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        List<Reservation> reservations = Service.GetAllReservations() ?? new List<Reservation>();
        DataTable reservationTable = new DataTable();
        reservationTable.Columns.Add("Id", typeof(int));
        reservationTable.Columns.Add("Destination", typeof(string));
        reservationTable.Columns.Add("ClientName", typeof(string));
        reservationTable.Columns.Add("ClientContact", typeof(string));
        reservationTable.Columns.Add("NumberOfReservedSeats", typeof(int));
        
        foreach (var reservation in reservations)
        {
            reservationTable.Rows.Add(reservation.Id, reservation.Trip.Destination, reservation.ClientName, reservation.ClientContact, reservation.NumberOfReservedSeats);
        }
        
        ReservationsDataGridView.DataSource = reservationTable;
    }
    
    private void BookTripButton_Click(object sender, EventArgs e)
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
        if (TripsDataGridView.SelectedRows.Count == 0)
        {
            MessageBox.Show("Please select a trip.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
        DataGridViewRow selectedRow = TripsDataGridView.SelectedRows[0];
        int selectedTripId = Convert.ToInt32(selectedRow.Cells["Id"].Value);
        Trip selectedTrip = Service.GetTripById(selectedTripId);
        try
        {
            Reservation reservation = new Reservation(selectedTrip, clientName, clientContact, seats);
            Service.AddReservation(reservation);
            MessageBox.Show("Trip reserved successfully!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            List<Trip> trips = Service.GetAllTrips() ?? new List<Trip>();
            LoadTrips(trips);
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
    
    private void TripsDataGridView_SelectionChanged(object sender, EventArgs e)
    {
        if (TripsDataGridView.SelectedRows.Count > 0)
        {
            DataGridViewRow selectedRow = TripsDataGridView.SelectedRows[0];
            int selectedTripId = Convert.ToInt32(selectedRow.Cells["Id"].Value);
            Trip selectedTrip = Service.GetTripById(selectedTripId);
            if (selectedTrip != null)
            {
                TxtBoxDestination.Text = selectedTrip.Destination;
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
        
        List<Trip> trips = Service.SearchTripsByDestTime(destination, departureDate, startTime, endTime);
        LoadTrips(trips);
    }

    private void ViewTrips_Click(object sender, EventArgs e)
    {
        List<Trip> trips = Service.GetAllTrips() ?? new List<Trip>();
        LoadTrips(trips);
    }

    private void LogOutButton_Click(object sender, EventArgs e)
    {
        this.Close();
    }
}
