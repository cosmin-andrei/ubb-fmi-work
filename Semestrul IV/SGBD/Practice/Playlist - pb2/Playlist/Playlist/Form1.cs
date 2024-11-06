using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Playlist
{
    public partial class Form1 : Form
    {
        private string _connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10; Database=Playlist;
        Integrated Security=true;TrustServerCertificate=true;";

        DataSet _ds = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        public Form1()
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

                    _parentAdapter = new SqlDataAdapter("SELECT * FROM Artist;", conn);
                    _childAdapter = new SqlDataAdapter("SELECT * FROM Melodie;", conn);
                    _parentAdapter.Fill(_ds, "Artisti");
                    _childAdapter.Fill(_ds, "Melodii");

                    DataColumn pkColumn = _ds.Tables["Artisti"].Columns["id_artist"];
                    DataColumn fkColumn = _ds.Tables["Melodii"].Columns["id_artist"];
                    DataRelation relation = new DataRelation("FK_Artisti_Melodii", pkColumn, fkColumn);
                    _ds.Relations.Add(relation);

                    _bsParent = new BindingSource();
                    _bsChild = new BindingSource();
                    _bsParent.DataSource = _ds.Tables["Artisti"];
                    listBoxParent.DataSource = _bsParent;
                    listBoxParent.DisplayMember = "nume";
                    listBoxParent.ValueMember = "id_artist";
                    _bsChild.DataSource = _bsParent;
                    _bsChild.DataMember = "FK_Artisti_Melodii";
                    dataGridViewChild.DataSource = _bsChild;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        // ADD BUTTON
        private void button2_Click(object sender, EventArgs e)
        {
            if (listBoxParent.SelectedIndex == -1)
            {
                MessageBox.Show(@"Selecteaza un artist");
            }
            else
            {
                DataRowView selectedRow = (DataRowView)listBoxParent.SelectedItem;
                int id = (int)selectedRow.Row["id_artist"];
                string numeMelodie = numeMel_textBox.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd = new SqlCommand("INSERT INTO Melodie (id_artist, nume) VALUES (@id, @nume)",
                        conn);
                    cmd.Parameters.AddWithValue("@id", id);
                    cmd.Parameters.AddWithValue("@nume", numeMelodie);
                    cmd.ExecuteNonQuery();
                }

                numeMel_textBox.Text = "";
                RefreshData_button_Click();
            }
        }

        // Update Button
        private void button3_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 0)
            {
                MessageBox.Show(@"Selecteaza o melodie");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"Selecteaza o singura melodie");
            }
            else
            {
                DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                if (selectedRow != null)
                {
                    int id = (int)selectedRow.Cells["id_melodie"].Value;
                    string numeMelodie = numeMel_textBox.Text;

                    using (SqlConnection conn = new SqlConnection(_connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("UPDATE Melodie SET nume = @nume WHERE id_melodie = @id",
                            conn);
                        cmd.Parameters.AddWithValue("@id", id);
                        cmd.Parameters.AddWithValue("@nume", numeMelodie);
                        cmd.ExecuteNonQuery();
                    }

                    numeMel_textBox.Text = "";
                    RefreshData_button_Click();
                }
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 0)
            {
                MessageBox.Show(@"Selecteaza o melodie");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"Selecteaza o singura melodie");
            }
            else
            {
                DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                if (selectedRow != null)
                {
                    int id = (int)selectedRow.Cells["id_melodie"].Value;
                    using (SqlConnection conn = new SqlConnection(_connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("DELETE FROM Melodie WHERE id_melodie = @id", conn);
                        cmd.Parameters.AddWithValue("@id", id);
                        cmd.ExecuteNonQuery();
                    }

                    numeMel_textBox.Text = "";
                    RefreshData_button_Click();
                }
            }
        }

        private void RefreshData_button_Click()
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    _parentAdapter.SelectCommand.Connection = conn;
                    _childAdapter.SelectCommand.Connection = conn;
                    
                    _ds.Tables["Melodii"].Clear();

                    _childAdapter.Fill(_ds, "Melodii");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void listBoxParent_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBoxParent.SelectedIndex != -1)
            {
                DataRowView selectedRow = (DataRowView)listBoxParent.SelectedItem;
                int id = (int)selectedRow.Row["id_artist"];
                DataRow[] childRows = selectedRow.Row.GetChildRows("FK_Artisti_Melodii");
                DataTable dt = new DataTable();
                dt.Columns.Add("id_melodie");
                dt.Columns.Add("nume");
                foreach (DataRow row in childRows)
                {
                    dt.Rows.Add(row["id_melodie"], row["nume"]);
                }

                dataGridViewChild.DataSource = dt;
            }
        }


        private void dataGridViewChild_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 1)
            {
                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];

                string melodieName = selectedRow.Cells["nume"].Value.ToString();
                Console.WriteLine(melodieName);
                numeMel_textBox.Text = melodieName;
            }
        }
    }
}
