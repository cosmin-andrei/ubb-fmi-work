using System.Data;
using System.Data.SqlClient;

namespace Cofetarie;

public partial class Form1 : Form
{
    string _connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10; Database=Cofetarie;
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

                _parentAdapter = new SqlDataAdapter("SELECT * FROM Laborator;", conn);
                _childAdapter = new SqlDataAdapter("SELECT * FROM Briosa;", conn);

                _parentAdapter.Fill(_ds, "Laboratoare");
                _childAdapter.Fill(_ds, "Briose");

                DataColumn pkColumn = _ds.Tables["Laboratoare"].Columns["id_laborator"];
                DataColumn fkColumn = _ds.Tables["Briose"].Columns["id_laborator"];
                DataRelation relation = new DataRelation("FK_Laboratoare_Briose", pkColumn, fkColumn);
                _ds.Relations.Add(relation);

                _bsParent = new BindingSource();
                _bsChild = new BindingSource();
                _bsParent.DataSource = _ds.Tables["Laboratoare"];
                dataGridViewParent.DataSource = _bsParent;
                _bsChild.DataSource = _bsParent;
                _bsChild.DataMember = "FK_Laboratoare_Briose";
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

                _ds.Tables["Briose"].Clear();
                _ds.Tables["Laboratoare"].Clear();

                _parentAdapter.Fill(_ds, "Evenimente");
                _childAdapter.Fill(_ds, "Participanti");
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message);
        }
    }
    
    private void buttonDelete_Click_1()
    {
        if (dataGridViewChild.SelectedRows.Count == 0)
        {
            MessageBox.Show(@"Selecteaza o briosa!");
        }
        else if (dataGridViewChild.SelectedRows.Count > 1)
        {
            MessageBox.Show(@"O singura briosa!");
        }
        else
        {
            try
            {
                //extragere rand + id
                DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                if (selectedRow != null)
                {
                    int briosaID = (int)selectedRow.Cells["id_briosa"].Value;

                    using (SqlConnection conn = new SqlConnection(_connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("DELETE FROM Briosa WHERE id_briosa = @briosaID",
                            conn);
                        cmd.Parameters.AddWithValue("@briosaID", briosaID);
                        cmd.ExecuteNonQuery();
                    }
                }

                textBoxBriosaName.Text = "";
                buttonRefresh_Click();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
    
    private void buttonUpdate_Click_1()
    {
        try
        {
            if (dataGridViewChild.SelectedRows.Count == 0)
            {
                MessageBox.Show(@"Selecteaza o briosa!");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"O singura briosa!");
            }
            else
            {
                DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                if (selectedRow != null)
                {
                    int briosaID = (int)selectedRow.Cells["id_briosa"].Value;
                    string briosaName = (string)selectedRow.Cells["nume"].Value;

                    using (SqlConnection conn = new SqlConnection(_connectionString))
                    {
                        conn.Open();
                        SqlCommand cmd = new SqlCommand("UPDATE Briosa SET nume_briosa = @briosaName WHERE id_briosa = @briosaID",
                            conn);
                        cmd.Parameters.AddWithValue("@briosaID", briosaID);
                        cmd.Parameters.AddWithValue("@briosaName", briosaName);
                        cmd.ExecuteNonQuery();
                    }
                }

                buttonRefresh_Click();
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message);
        }
    }
    
    private void buttonAdd_Click_1()
    {
        try
        {
            string briosaName = textBoxBriosaName.Text;

            using (SqlConnection conn = new SqlConnection(_connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand("INSERT INTO Briosa(nume_briosa) VALUES(@briosaName);",
                    conn);
                cmd.Parameters.AddWithValue("@briosaName", briosaName);
                cmd.ExecuteNonQuery();
            }

            textBoxBriosaName.Text = "";
            buttonRefresh_Click();
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message);
        }
    }
    
    private void dataGridViewChild_SelectionChanged(object sender, EventArgs e)
    {
        if (dataGridViewChild.SelectedRows.Count == 0)
        {
            return;
        }

        DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
        textBoxBriosaName.Text = (string)selectedRow.Cells["nume"].Value;
    }

    private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
    {
        if (dataGridViewParent.SelectedRows.Count == 0)
        {
            return;
        }

        DataGridViewRow selectedRow = dataGridViewParent.SelectedRows[0];
        textBoxEventID.Text = selectedRow.Cells["id_laborator"].Value.ToString();
        textBoxBriosaName.Text = "";
    }



}