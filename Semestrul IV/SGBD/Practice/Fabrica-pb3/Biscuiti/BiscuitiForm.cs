using System.Data;
using System.Data.SqlClient;

namespace Biscuiti
{
    public partial class BiscuitiForm : Form
    {
        string _connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10; Database=Fabrica;
        Integrated Security=true;TrustServerCertificate=true;";
        
        DataSet _ds = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        public BiscuitiForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();

                    _parentAdapter = new SqlDataAdapter("SELECT * FROM Producator;", conn);
                    _childAdapter = new SqlDataAdapter("SELECT * FROM Biscuite;", conn);
                    _parentAdapter.Fill(_ds, "Producatori");
                    _childAdapter.Fill(_ds, "Biscuiti");

                    DataColumn pkColumn = _ds.Tables["Producatori"].Columns["id_producator"];
                    DataColumn fkColumn = _ds.Tables["Biscuiti"].Columns["id_producator"];
                    DataRelation relation = new DataRelation("FK_Producatori_Biscuiti", pkColumn, fkColumn);
                    _ds.Relations.Add(relation);

                    _bsParent = new BindingSource();
                    _bsChild = new BindingSource();
                    _bsParent.DataSource = _ds.Tables["Producatori"];
                    dataGridViewParent.DataSource = _bsParent;
                    _bsChild.DataSource = _bsParent;
                    _bsChild.DataMember = "FK_Producatori_Biscuiti";
                    dataGridViewChild.DataSource = _bsChild;

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonRefresh_Click()
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    _parentAdapter.SelectCommand.Connection = conn;
                    _childAdapter.SelectCommand.Connection = conn;

                    _ds.Tables["Biscuiti"].Clear();
                    
 

                    _childAdapter.Fill(_ds, "Biscuiti");
              
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonDelete_Click_1(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 0)
            {
                MessageBox.Show(@"Selecteaza un biscuite!");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"Un singur biscuite!");
            }
            else
                try
                {
                    DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                    if (selectedRow != null)
                    {
                        int biscuiteId = (int)selectedRow.Cells["id_biscuite"].Value;

                        using (SqlConnection conn = new SqlConnection(_connectionString))
                        {
                            conn.Open();
                            SqlCommand cmd = new SqlCommand("DELETE FROM Biscuite WHERE id_biscuite = @biscuiteId",
                                conn);
                            cmd.Parameters.AddWithValue("@biscuiteId", biscuiteId);
                            cmd.ExecuteNonQuery();
                        }
                    }

                    textBoxBiscuitiName.Text = "";
                    buttonRefresh_Click();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
        }

        private void buttonUpdate_Click_1(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewChild.SelectedRows.Count == 0)
                {
                    MessageBox.Show(@"Selectati un biscuite");
                    return;
                }

                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
                int biscuiteId = (int)selectedRow.Cells["id_biscuite"].Value;

                string updatedBiscuiteName = textBoxBiscuitiName.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "UPDATE Biscuite SET nume_biscuite = @biscuiteName WHERE id_biscuite = @biscuiteId",
                            conn);
                    cmd.Parameters.AddWithValue("@biscuiteName", updatedBiscuiteName);
                    cmd.Parameters.AddWithValue("@biscuiteId", biscuiteId);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Biscuite actualizat!");
                textBoxBiscuitiName.Text = "";
                buttonRefresh_Click();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonAdd_Click_1(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(textBoxProducatorID.Text))
                {
                    MessageBox.Show(@"Selecteaza un producator");
                    return;
                }
                else if (string.IsNullOrWhiteSpace(textBoxBiscuitiName.Text))
                {
                    MessageBox.Show(@"Completati toate campurile!");
                    return;
                }

                int producatorId = int.Parse(textBoxProducatorID.Text);
                string biscuiteName = textBoxBiscuitiName.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "INSERT INTO Biscuite (id_producator, nume_biscuite) VALUES (@producatorId, @biscuiteName)",
                            conn);
                    cmd.Parameters.AddWithValue("@producatorId", producatorId);
                    cmd.Parameters.AddWithValue("@biscuiteName", biscuiteName);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Biscuite adaugat");
                textBoxBiscuitiName.Text = "";
                buttonRefresh_Click();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        private void dataGridViewChild_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 1)
            {
                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];

                string biscuiteName = selectedRow.Cells["nume_biscuite"].Value.ToString();
               
                textBoxBiscuitiName.Text = biscuiteName;
            }
        }

        private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridViewParent.SelectedRows[0];


                int producatorId = (int)selectedRow.Cells["id_producator"].Value;

                textBoxProducatorID.Text = producatorId.ToString();
                textBoxBiscuitiName.Text = "";
            }
        }
    }
}