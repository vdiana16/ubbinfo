using System.Data;
using System.Data.SqlClient;

namespace lab1sgbd
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source=DESKTOP-KGC3UTN\\SQLEXPRESS02;Initial Catalog=MagazinulNaturii;Integrated Security=True");
        SqlDataAdapter daParent = new SqlDataAdapter();
        SqlDataAdapter daChild = new SqlDataAdapter();
        DataSet ds = new DataSet();
        BindingSource bsParent = new BindingSource();
        BindingSource bsChild = new BindingSource();

        public Form1()
        {
            InitializeComponent();
            LoadData();
        }

        private void LoadData()
        {
            try
            {
                cs.Open();

                daParent.SelectCommand = new SqlCommand("SELECT * FROM Producator", cs);
                daParent.Fill(ds, "Producator");
                bsParent.DataSource = ds.Tables["Producator"];
                dataGridViewParent.DataSource = bsParent;

                daChild.SelectCommand = new SqlCommand("SELECT * FROM Produs", cs);
                daChild.Fill(ds, "Produs");
                DataRelation relation = new DataRelation("FK_Producator_Produs",
                    ds.Tables["Producator"].Columns["IdProducator"],
                    ds.Tables["Produs"].Columns["IdProducator"]);
                ds.Relations.Add(relation);

                bsChild.DataSource = bsParent;
                bsChild.DataMember = "FK_Producator_Produs";
                dataGridViewChild.DataSource = bsChild;

                dataGridViewParent.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridViewChild.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridViewParent.AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);
                dataGridViewChild.AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare " + ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }

        private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (bsParent.Current != null)
            {
                bsChild.Filter = "IdProducator = " + ((DataRowView)bsParent.Current)["IdProducator"];
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtName.Text))
            {
                MessageBox.Show("Completează câmpul Nume Produs.");
                return;
            }

            if (string.IsNullOrEmpty(txtPrice.Text) || !float.TryParse(txtPrice.Text, out float price) || price <= 0)
            {
                MessageBox.Show("Introdu un preț valid.");
                return;
            }

            if (dtpExpirationDate.Value <= dtpProductionDate.Value)
            {
                MessageBox.Show("Data Expirare trebuie să fie după Data Fabricare.");
                return;
            }

            try
            {
                cs.Open();
                SqlCommand cmd = new SqlCommand("INSERT INTO Produs (NumeProdus, Pret, DataFabricare, DataExpirare, IdProducator) VALUES (@nume, @pret, @dataFabricare, @dataExpirare, @idProducator)", cs);
                cmd.Parameters.AddWithValue("@nume", txtName.Text);
                cmd.Parameters.AddWithValue("@pret", float.Parse(txtPrice.Text));
                cmd.Parameters.AddWithValue("@dataFabricare", dtpProductionDate.Value);
                cmd.Parameters.AddWithValue("@dataExpirare", dtpExpirationDate.Value);
                cmd.Parameters.AddWithValue("@idProducator", ((DataRowView)bsParent.Current)["IdProducator"]);

                cmd.ExecuteNonQuery();
                ds.Tables["Produs"].Clear();
                daChild.Fill(ds, "Produs");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare " + ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }

        private void btnDelete_Click(object sender, EventArgs args)
        {
            if (bsChild.Current == null)
            {
                MessageBox.Show("Selectează un produs pentru a-l șterge.");
                return;
            }

            try
            {
                cs.Open();
                int idProdus = (int)((DataRowView)bsChild.Current)["IdProdus"];
                SqlCommand cmd = new SqlCommand("DELETE FROM Produs WHERE IdProdus = @id", cs);
                cmd.Parameters.AddWithValue("@id", idProdus);
                cmd.ExecuteNonQuery();
                ds.Tables["Produs"].Clear();
                daChild.Fill(ds, "Produs");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare " + ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }

        private void btnUpdate_Click(object sender, EventArgs eventArgs)
        {
            if (bsChild.Current == null)
            {
                MessageBox.Show("Selectează un produs pentru a-l șterge.");
                return;
            }

            if (string.IsNullOrEmpty(txtName.Text))
            {
                MessageBox.Show("Completează câmpul Nume Produs.");
                return;
            }

            if (string.IsNullOrEmpty(txtPrice.Text) || !float.TryParse(txtPrice.Text, out float price) || price <= 0)
            {
                MessageBox.Show("Introdu un preț valid.");
                return;
            }

            if (dtpExpirationDate.Value <= dtpProductionDate.Value)
            {
                MessageBox.Show("Data Expirare trebuie să fie după Data Fabricare.");
                return;
            }


            try
            {
                cs.Open();
                int idProdus = (int)((DataRowView)bsChild.Current)["IdProdus"];
                SqlCommand cmd = new SqlCommand("UPDATE Produs SET NumeProdus = @numeProdus, Pret = @pret, DataFabricare = @dataFabricare, DataExpirare = @dataExpirare WHERE IdProdus = @id", cs);
                cmd.Parameters.AddWithValue("@numeProdus", txtName.Text);
                cmd.Parameters.AddWithValue("@pret", txtPrice.Text);
                cmd.Parameters.AddWithValue("@dataFabricare", dtpProductionDate.Value);
                cmd.Parameters.AddWithValue("@dataExpirare", dtpExpirationDate.Value);
                cmd.Parameters.AddWithValue("@id", idProdus);
                cmd.ExecuteNonQuery();
                ds.Tables["Produs"].Clear();
                daChild.Fill(ds, "Produs");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare " + ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }
    }
}
