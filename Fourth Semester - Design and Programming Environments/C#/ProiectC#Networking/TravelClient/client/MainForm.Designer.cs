using System.ComponentModel;

namespace TravelClient.client;

partial class MainForm
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
        LblTours = new System.Windows.Forms.Label();
        LblClientDetails = new System.Windows.Forms.Label();
        LblReservations = new System.Windows.Forms.Label();
        ToursDataGridView = new System.Windows.Forms.DataGridView();
        ReservationsDataGridView = new System.Windows.Forms.DataGridView();
        TxtBoxClientName = new System.Windows.Forms.TextBox();
        TxtBoxClientContact = new System.Windows.Forms.TextBox();
        TxtBoxNumberOfSeats = new System.Windows.Forms.TextBox();
        BtnBookTour = new System.Windows.Forms.Button();
        LblSearch = new System.Windows.Forms.Label();
        TxtBoxDestination = new System.Windows.Forms.TextBox();
        BtnSearch = new System.Windows.Forms.Button();
        TxtBoxStartTime = new System.Windows.Forms.TextBox();
        TxtBoxEndTime = new System.Windows.Forms.TextBox();
        DtpDepartureTime = new System.Windows.Forms.DateTimePicker();
        BtnViewTours = new System.Windows.Forms.Button();
        BtnLogOut = new System.Windows.Forms.Button();
        ((System.ComponentModel.ISupportInitialize)ToursDataGridView).BeginInit();
        ((System.ComponentModel.ISupportInitialize)ReservationsDataGridView).BeginInit();
        SuspendLayout();
        // 
        // LblTours
        // 
        LblTours.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold);
        LblTours.Location = new System.Drawing.Point(411, 20);
        LblTours.Name = "LblTours";
        LblTours.Size = new System.Drawing.Size(200, 30);
        LblTours.TabIndex = 0;
        LblTours.Text = "Available Tours";
        // 
        // LblClientDetails
        // 
        LblClientDetails.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold);
        LblClientDetails.Location = new System.Drawing.Point(20, 20);
        LblClientDetails.Name = "LblClientDetails";
        LblClientDetails.Size = new System.Drawing.Size(200, 30);
        LblClientDetails.TabIndex = 2;
        LblClientDetails.Text = "Client Details";
        // 
        // LblReservations
        // 
        LblReservations.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold);
        LblReservations.Location = new System.Drawing.Point(398, 454);
        LblReservations.Name = "LblReservations";
        LblReservations.Size = new System.Drawing.Size(200, 30);
        LblReservations.TabIndex = 7;
        LblReservations.Text = "Reservations";
        // 
        // ToursDataGridView
        // 
        ToursDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
        ToursDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        ToursDataGridView.Location = new System.Drawing.Point(411, 60);
        ToursDataGridView.Name = "ToursDataGridView";
        ToursDataGridView.RowHeadersWidth = 51;
        ToursDataGridView.Size = new System.Drawing.Size(650, 322);
        ToursDataGridView.TabIndex = 1;
        ToursDataGridView.CellFormatting += ToursDataGridViewCellFormatting;
        ToursDataGridView.SelectionChanged += ToursDataGridViewSelectionChanged;
        // 
        // ReservationsDataGridView
        // 
        ReservationsDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
        ReservationsDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        ReservationsDataGridView.Location = new System.Drawing.Point(20, 496);
        ReservationsDataGridView.Name = "ReservationsDataGridView";
        ReservationsDataGridView.RowHeadersWidth = 51;
        ReservationsDataGridView.Size = new System.Drawing.Size(950, 212);
        ReservationsDataGridView.TabIndex = 8;
        // 
        // TxtBoxClientName
        // 
        TxtBoxClientName.Location = new System.Drawing.Point(20, 60);
        TxtBoxClientName.Name = "TxtBoxClientName";
        TxtBoxClientName.PlaceholderText = "Client Name";
        TxtBoxClientName.Size = new System.Drawing.Size(200, 27);
        TxtBoxClientName.TabIndex = 3;
        // 
        // TxtBoxClientContact
        // 
        TxtBoxClientContact.Location = new System.Drawing.Point(20, 100);
        TxtBoxClientContact.Name = "TxtBoxClientContact";
        TxtBoxClientContact.PlaceholderText = "Client Contact";
        TxtBoxClientContact.Size = new System.Drawing.Size(200, 27);
        TxtBoxClientContact.TabIndex = 4;
        // 
        // TxtBoxNumberOfSeats
        // 
        TxtBoxNumberOfSeats.Location = new System.Drawing.Point(20, 140);
        TxtBoxNumberOfSeats.Name = "TxtBoxNumberOfSeats";
        TxtBoxNumberOfSeats.PlaceholderText = "Number of Seats";
        TxtBoxNumberOfSeats.Size = new System.Drawing.Size(200, 27);
        TxtBoxNumberOfSeats.TabIndex = 5;
        // 
        // BtnBookTour
        // 
        BtnBookTour.Location = new System.Drawing.Point(241, 100);
        BtnBookTour.Name = "BtnBookTour";
        BtnBookTour.Size = new System.Drawing.Size(146, 30);
        BtnBookTour.TabIndex = 6;
        BtnBookTour.Text = "Reserve Tour";
        BtnBookTour.Click += BookTourButton_Click;
        // 
        // LblSearch
        // 
        LblSearch.Location = new System.Drawing.Point(20, 195);
        LblSearch.Name = "LblSearch";
        LblSearch.Size = new System.Drawing.Size(100, 35);
        LblSearch.TabIndex = 9;
        LblSearch.Text = "Search Tours";
        // 
        // TxtBoxDestination
        // 
        TxtBoxDestination.Location = new System.Drawing.Point(19, 233);
        TxtBoxDestination.Name = "TxtBoxDestination";
        TxtBoxDestination.PlaceholderText = "Destination";
        TxtBoxDestination.Size = new System.Drawing.Size(200, 27);
        TxtBoxDestination.TabIndex = 10;
        // 
        // BtnSearch
        // 
        BtnSearch.Location = new System.Drawing.Point(267, 287);
        BtnSearch.Name = "BtnSearch";
        BtnSearch.Size = new System.Drawing.Size(105, 43);
        BtnSearch.TabIndex = 11;
        BtnSearch.Text = "Search Tours";
        BtnSearch.UseVisualStyleBackColor = true;
        BtnSearch.Click += SearchButton_Click;
        // 
        // TxtBoxStartTime
        // 
        TxtBoxStartTime.Location = new System.Drawing.Point(19, 276);
        TxtBoxStartTime.Name = "TxtBoxStartTime";
        TxtBoxStartTime.PlaceholderText = "From Time";
        TxtBoxStartTime.Size = new System.Drawing.Size(201, 27);
        TxtBoxStartTime.TabIndex = 13;
        // 
        // TxtBoxEndTime
        // 
        TxtBoxEndTime.Location = new System.Drawing.Point(20, 322);
        TxtBoxEndTime.Name = "TxtBoxEndTime";
        TxtBoxEndTime.PlaceholderText = "Until Time";
        TxtBoxEndTime.Size = new System.Drawing.Size(199, 27);
        TxtBoxEndTime.TabIndex = 14;
        // 
        // DtpDepartureTime
        // 
        DtpDepartureTime.CustomFormat = "yyyy//MM/dd HH:mm";
        DtpDepartureTime.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
        DtpDepartureTime.Location = new System.Drawing.Point(19, 371);
        DtpDepartureTime.Name = "DtpDepartureTime";
        DtpDepartureTime.Size = new System.Drawing.Size(200, 27);
        DtpDepartureTime.TabIndex = 12;
        // 
        // BtnViewTours
        // 
        BtnViewTours.Location = new System.Drawing.Point(411, 402);
        BtnViewTours.Name = "BtnViewTours";
        BtnViewTours.Size = new System.Drawing.Size(100, 29);
        BtnViewTours.TabIndex = 15;
        BtnViewTours.Text = "View Tours";
        BtnViewTours.UseVisualStyleBackColor = true;
        BtnViewTours.Click += ViewTours_Click;
        //
        //BtnLogOut
        //  
        BtnLogOut.Location = new System.Drawing.Point(1022, 676);
        BtnLogOut.Name = "BtnLogOut";
        BtnLogOut.Size = new System.Drawing.Size(114, 31);
        BtnLogOut.TabIndex = 16;
        BtnLogOut.Text = "Log Out";
        BtnLogOut.UseVisualStyleBackColor = true;
        BtnLogOut.Click += LogOutButton_Click;
        // 
        // MainForm
        // 
        AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        ClientSize = new System.Drawing.Size(1300, 726);
        Controls.Add(BtnLogOut);
        Controls.Add(BtnViewTours);
        Controls.Add(DtpDepartureTime);
        Controls.Add(TxtBoxEndTime);
        Controls.Add(TxtBoxStartTime);
        Controls.Add(BtnSearch);
        Controls.Add(TxtBoxDestination);
        Controls.Add(LblSearch);
        Controls.Add(LblTours);
        Controls.Add(ToursDataGridView);
        Controls.Add(LblClientDetails);
        Controls.Add(TxtBoxClientName);
        Controls.Add(TxtBoxClientContact);
        Controls.Add(TxtBoxNumberOfSeats);
        Controls.Add(BtnBookTour);
        Controls.Add(LblReservations);
        Controls.Add(ReservationsDataGridView);
        Text = "MainForm";
        Load += LoadMain;
        ((System.ComponentModel.ISupportInitialize)ToursDataGridView).EndInit();
        ((System.ComponentModel.ISupportInitialize)ReservationsDataGridView).EndInit();
        ResumeLayout(false);
        PerformLayout();
    }

    private System.Windows.Forms.Button BtnLogOut;

    private System.Windows.Forms.Button BtnViewTours;

    private System.Windows.Forms.Label LblSearch;
    private System.Windows.Forms.TextBox TxtBoxDestination;
    private System.Windows.Forms.Button BtnSearch;
    private System.Windows.Forms.TextBox TxtBoxStartTime;
    private System.Windows.Forms.TextBox TxtBoxEndTime;
    private System.Windows.Forms.DateTimePicker DtpDepartureTime;

    #endregion
    private System.Windows.Forms.Label LblTours;
    private Label LblClientDetails;
    private System.Windows.Forms.Label LblReservations;
    
    private System.Windows.Forms.DataGridView ToursDataGridView;
    private System.Windows.Forms.DataGridView ReservationsDataGridView;
    private System.Windows.Forms.TextBox TxtBoxClientName;
    private System.Windows.Forms.TextBox TxtBoxClientContact;
    private System.Windows.Forms.TextBox TxtBoxNumberOfSeats;
    private System.Windows.Forms.Button BtnBookTour;
}
    
