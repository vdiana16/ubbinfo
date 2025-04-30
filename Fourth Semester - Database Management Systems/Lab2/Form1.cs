using System.Configuration;
using System.Data;
using System.Data.SqlClient;


namespace lab2sgbd
{
    public partial class Form1 : Form
    {
        static string connectionString = ConfigurationManager.ConnectionStrings["connection"].ConnectionString;
        SqlConnection connection = new SqlConnection(connectionString);
        SqlDataAdapter daParent = new SqlDataAdapter();
        SqlDataAdapter daChild = new SqlDataAdapter();
        DataSet dsParent = new DataSet();
        DataSet dsChild = new DataSet();

        public Form1()
        {
            InitializeComponent();
        }

        private void LoadData(object sender, EventArgs e)
        {
            try
            {
                connection.Open();
                string selectStatement = ConfigurationManager.AppSettings["ParentSelectStatement"];
                daParent.SelectCommand = new SqlCommand(selectStatement, connection);
                dsParent.Clear();

                daParent.Fill(dsParent);
                dataGridViewParent.DataSource = dsParent.Tables[0];

                generateTextBoxesParent();
                generateTextBoxesChild();
                labelParent.Text = ConfigurationManager.AppSettings["ParentTableName"];
                labelChild.Text = ConfigurationManager.AppSettings["ChildTableName"];

            }
            catch (Exception ex)
            {
                labelMessage.Text += ex.Message;
                labelMessage.ForeColor = Color.Red;
                connection.Close();
            }
            finally
            {
                connection.Close();
            }
        }

        private void dataGridParent_Click(object sender, DataGridViewCellEventArgs e)
        {
            labelMessage.Text = "";

            List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ParentColumnNames"].Split(','));
            int i = 0;
            int id = -1;
            int selectedParentId = -1;
            string parentId = ConfigurationManager.AppSettings["ParentId"];
            foreach (string columnName in columnNames)
            {
                TextBox textBox = (TextBox)panelParent.Controls[columnName];
                textBox.Text = dataGridViewParent.CurrentRow.Cells[i].FormattedValue.ToString();
                if (columnName == parentId)
                    id = Int32.Parse(textBox.Text);
                i++;
            }


            try
            {
                string selectStatement = ConfigurationManager.AppSettings["ChildSelectStatement"];

                daChild.SelectCommand = new SqlCommand(selectStatement, connection);
                daChild.SelectCommand.Parameters.AddWithValue("@" + parentId, id);

                dsChild.Clear();
                daChild.Fill(dsChild);
                dataGridViewChild.DataSource = dsChild.Tables[0];
            }
            catch (Exception ex)
            {
                labelMessage.Text += ex.Message;
                labelMessage.ForeColor = Color.DarkRed;
                connection.Close();
            }

            

        }

        private void dataGridChild_Click(object sender, DataGridViewCellEventArgs e)
        {
            List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
            int i = 0;
            foreach (string columnName in columnNames)
            {
                TextBox textBox = (TextBox)panelChild.Controls[columnName];
                textBox.Text = dataGridViewChild.CurrentRow.Cells[i].FormattedValue.ToString();
                i++;
            }

        }

        private void generateTextBoxesParent()
        {
            List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ParentColumnNames"].Split(','));
            int pointX = 10;
            int pointY = 10;
            panelParent.Controls.Clear();
            foreach (string columnName in columnNames)
            {
                Label label = new Label
                {
                    Text = columnName,
                    Name = "Label" + columnName,
                    Location = new Point(pointX, pointY),
                    Visible = true,
                    Parent = panelParent
                };

                TextBox textBox = new TextBox
                {
                    Name = columnName,
                    Location = new Point(pointX + label.Width, pointY),
                    Visible = true,
                    Enabled = false,
                    Parent = panelParent
                };

                pointY += 35;
                panelParent.Show();
            }
        }

        private void generateTextBoxesChild()
        {
            List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
            string parentId = ConfigurationManager.AppSettings["ParentId"];
            string childId = ConfigurationManager.AppSettings["ChildId"];

            int pointX = 10;
            int pointY = 10;
            panelChild.Controls.Clear();

            foreach (string columnName in columnNames)
            {
                Label label = new Label
                {
                    Text = columnName,
                    Name = columnName + "Label",
                    Location = new Point(pointX, pointY),
                    Visible = true,
                    Parent = panelChild
                };

                TextBox textBox = new TextBox
                {
                    Name = columnName,
                    Location = new Point(pointX + label.Width, pointY),
                    Visible = true,
                    Parent = panelChild
                };

                if (columnName == parentId || columnName == childId)
                    textBox.Enabled = false;

                pointY += 35;
                panelChild.Show();
            }

        }




        private void addButton_Click(object sender, EventArgs e)
        {
            labelMessage.Text = "";
            try
            {
                string InsertStatement = ConfigurationManager.AppSettings["InsertStatement"];
                List<string> commandParameters = new List<string>(ConfigurationManager.AppSettings["InsertCommandParameters"].Split(','));
                List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));

                daChild.InsertCommand = new SqlCommand(InsertStatement, connection);
                foreach (string columnName in columnNames)
                {
                    if (commandParameters.Where(x => x.Contains(columnName)).FirstOrDefault() != null)
                    {
                        TextBox textBox = (TextBox)panelChild.Controls[columnName];
                        if (textBox.Text == "" && columnName != "id")
                        {
                            throw new Exception("Date invalide!");
                        }
                        daChild.InsertCommand.Parameters.AddWithValue("@" + columnName, textBox.Text);
                    }
                }

                connection.Open();
                daChild.InsertCommand.ExecuteNonQuery();
                connection.Close();

                labelMessage.Text = "Adaugarea a fost realizata cu succes!";
                labelMessage.ForeColor = Color.Green;

                dsChild.Clear();
                daChild.Fill(dsChild);
                dataGridViewChild.DataSource = dsChild.Tables[0];
            }
            catch (Exception ex)
            {
                labelMessage.Text += ex.Message;
                labelMessage.ForeColor = Color.Red;
                connection.Close();
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            labelMessage.Text = "";

            List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
            int i = 0;
            int id = -1;
            string childId = ConfigurationManager.AppSettings["ChildId"];
            foreach (string columnName in columnNames)
            {
                if (columnName == childId)
                    id = Int32.Parse(dataGridViewChild.CurrentRow.Cells[i].FormattedValue.ToString());
                i++;
            }
            try
            {
                string DeleteStatement = ConfigurationManager.AppSettings["DeleteStatement"];

                daChild.DeleteCommand = new SqlCommand(DeleteStatement, connection);
                daChild.DeleteCommand.Parameters.AddWithValue("@" + childId, id);

                connection.Open();
                daChild.DeleteCommand.ExecuteNonQuery();
                connection.Close();

                labelMessage.Text = "Stergerea a fost realizata cu succes!";
                labelMessage.ForeColor = Color.Green;

                dsChild.Clear();
                daChild.Fill(dsChild);
                dataGridViewChild.DataSource = dsChild.Tables[0];
            }
            catch (Exception ex)
            {
                labelMessage.Text += ex.Message;
                labelMessage.ForeColor = Color.Red;
                connection.Close();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            labelMessage.Text = "";
            try
            {
                string UpdateStatement = ConfigurationManager.AppSettings["UpdateStatement"];
                List<string> commandParameters = new List<string>(ConfigurationManager.AppSettings["UpdateCommandParameters"].Split(','));
                List<string> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));

                daChild.UpdateCommand = new SqlCommand(UpdateStatement, connection);
                foreach (string columnName in columnNames)
                {
                    if (commandParameters.Where(x => x.Contains(columnName)).FirstOrDefault() != null)
                    {
                        TextBox textBox = (TextBox)panelChild.Controls[columnName];
                        if (textBox.Text == "")
                        {
                            throw new Exception("Date invalide!");
                        }
                        daChild.UpdateCommand.Parameters.AddWithValue("@" + columnName, textBox.Text);
                    }
                }

                connection.Open();
                daChild.UpdateCommand.ExecuteNonQuery();
                connection.Close();

                labelMessage.Text = "Modificarea a fost realizata cu succes!";
                labelMessage.ForeColor = Color.Green;

                dsChild.Clear();
                daChild.Fill(dsChild);
                dataGridViewChild.DataSource = dsChild.Tables[0];
            }
            catch (Exception ex)
            {
                labelMessage.Text += ex.Message;
                labelMessage.ForeColor = Color.Red;
                connection.Close();
            }
        }
    }

}
