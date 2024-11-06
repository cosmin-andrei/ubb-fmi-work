using System.Data;
using System.Data.SqlClient;

namespace ExamenSGBD
{
    public partial class InghetataForm : Form
    {
        string _connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10; Database=S9;
        Integrated Security=true;TrustServerCertificate=true;";

        DataSet _ds = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        public InghetataForm()
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

                    _parentAdapter = new SqlDataAdapter("SELECT * FROM TipuriInghetate;", conn);
                    _childAdapter = new SqlDataAdapter("SELECT * FROM Inghetate;", conn);
                    _parentAdapter.Fill(_ds, "TipuriInghetate");
                    _childAdapter.Fill(_ds, "Inghetate");

                    DataColumn pkColumn = _ds.Tables["TipuriInghetate"].Columns["Tid"];
                    DataColumn fkColumn = _ds.Tables["Inghetate"].Columns["Tid"];
                    DataRelation relation = new DataRelation("FK_TipuriInghetate_Inghetate", pkColumn, fkColumn);
                    _ds.Relations.Add(relation);

                    _bsParent = new BindingSource();
                    _bsChild = new BindingSource();
                    _bsParent.DataSource = _ds.Tables["TipuriInghetate"];
                    dataGridViewParent.DataSource = _bsParent;
                    _bsChild.DataSource = _bsParent;
                    _bsChild.DataMember = "FK_TipuriInghetate_Inghetate";
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

                    _ds.Tables["Inghetate"].Clear();



                    _childAdapter.Fill(_ds, "Inghetate");

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
                MessageBox.Show(@"Selecteaza o inghetata!");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"O singura inghetata!");
            }
            else
                try
                {
                    DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                    if (selectedRow != null)
                    {
                        int inghetataId = (int)selectedRow.Cells["Iid"].Value;

                        using (SqlConnection conn = new SqlConnection(_connectionString))
                        {
                            conn.Open();
                            SqlCommand cmd = new SqlCommand("DELETE FROM Inghetate WHERE Iid = @inghetataId",
                                conn);
                            cmd.Parameters.AddWithValue("@inghetataId", inghetataId);
                            cmd.ExecuteNonQuery();
                        }
                    }

                    textBoxDenumire.Text = "";
                    textBoxPret.Text = "";
                    textBoxGramaj.Text = "";
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
                    MessageBox.Show(@"Selectati o inghetata");
                    return;
                }

                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
                int inghetataId = (int)selectedRow.Cells["Iid"].Value;

                string updatedDenumire = textBoxDenumire.Text;
                string updatedPret = textBoxPret.Text;
                string updatedGramaj = textBoxGramaj.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "UPDATE Inghetate SET Denumire = @denumire, Gramaj = @gramaj, Pret = @pret WHERE Iid = @inghetataId",
                            conn);
                    cmd.Parameters.AddWithValue("@denumire", updatedDenumire);
                    cmd.Parameters.AddWithValue("@gramaj", updatedGramaj);
                    cmd.Parameters.AddWithValue("@pret", updatedPret);
                    cmd.Parameters.AddWithValue("@inghetataId", inghetataId);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Inghetata actualizata!");
                textBoxDenumire.Text = "";
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
                if (string.IsNullOrWhiteSpace(textBoxTipID.Text))
                {
                    MessageBox.Show(@"Selecteaza un tip de inghetata");
                    return;
                }

                if (string.IsNullOrWhiteSpace(textBoxDenumire.Text))
                {
                    MessageBox.Show(@"Completati toate campurile!");
                    return;
                }

                int tipId = int.Parse(textBoxTipID.Text);
                string denumire = textBoxDenumire.Text;
                string pret = textBoxPret.Text;
                string gramaj = textBoxGramaj.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "INSERT INTO Inghetate(Tid, Denumire, Pret, Gramaj) VALUES (@tipId, @denumire, @pret, @gramaj)",
                            conn);
                    cmd.Parameters.AddWithValue("@tipId", tipId);
                    cmd.Parameters.AddWithValue("@denumire", denumire);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@gramaj", gramaj);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Inghetata adaugata");
                textBoxDenumire.Text = "";
                textBoxPret.Text = "";
                textBoxGramaj.Text = "";
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

                string denumire = selectedRow.Cells["Denumire"].Value.ToString();
                string pret = selectedRow.Cells["Pret"].Value.ToString();
                string gramaj = selectedRow.Cells["Gramaj"].Value.ToString();

                textBoxDenumire.Text = denumire;
                textBoxPret.Text = pret;
                textBoxGramaj.Text = gramaj;
            }
        }

        private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridViewParent.SelectedRows[0];


                int tipId = (int)selectedRow.Cells["Tid"].Value;

                textBoxTipID.Text = tipId.ToString();
                textBoxDenumire.Text = "";
                textBoxPret.Text = "";
                textBoxGramaj.Text = "";
            }
        }
    }
}