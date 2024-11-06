using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace SGBDLAB
{
    public partial class ParticipantiForm : Form
    {
        string _connectionString = @"Server=DESKTOP-COR\SQLEXPRESS10; Database=Organizatie;
        Integrated Security=true;TrustServerCertificate=true;";

        //adaptor = interogari sql, preluam date din DB
        DataSet _ds = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        public ParticipantiForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                //deschid conexiunea cu DB
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    // MessageBox.Show("Starea conexiunii: " + conn.State.ToString());

                    //initializare adaptoare pt tabele
                    //adaptor = interogari sql, preluam date din DB
                    _parentAdapter = new SqlDataAdapter("SELECT * FROM Eveniment;", conn);
                    _childAdapter = new SqlDataAdapter("SELECT * FROM Participant;", conn);
                    _parentAdapter.Fill(_ds, "Evenimente");
                    _childAdapter.Fill(_ds, "Participanti");

                    //definesc relatia dintre tabele (PK, FK)
                    DataColumn pkColumn = _ds.Tables["Evenimente"].Columns["id_eveniment"];
                    DataColumn fkColumn = _ds.Tables["Participanti"].Columns["id_eveniment"];
                    DataRelation relation = new DataRelation("FK_Evenimente_Angajati", pkColumn, fkColumn);
                    _ds.Relations.Add(relation);

                    //BindingSource = conectam datele intre UI (DataGridView) si Dataset
                    _bsParent = new BindingSource();
                    _bsChild = new BindingSource();
                    _bsParent.DataSource = _ds.Tables["Evenimente"];
                    dataGridViewParent.DataSource = _bsParent;
                    _bsChild.DataSource = _bsParent;
                    _bsChild.DataMember = "FK_Evenimente_Angajati";
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
                    //apartine SQLDATAADAPTER - operatiune de refresh date pt ca s-a actualizat baza => update conexiune
                    _parentAdapter.SelectCommand.Connection = conn;
                    _childAdapter.SelectCommand.Connection = conn;

                    _ds.Tables["Participanti"].Clear();
                    _ds.Tables["Evenimente"].Clear();

                    _parentAdapter.Fill(_ds, "Evenimente");
                    _childAdapter.Fill(_ds, "Participanti");
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
                MessageBox.Show(@"Selecteaza un participant!");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"Un singur participant!");
            }
            else
                try
                {
                    //extragere rand + id
                    DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                    if (selectedRow != null)
                    {
                        int participantId = (int)selectedRow.Cells["id_participant"].Value;

                        using (SqlConnection conn = new SqlConnection(_connectionString))
                        {
                            conn.Open();
                            SqlCommand cmd = new SqlCommand("DELETE FROM Participant WHERE id_participant = @participantId",
                                conn);
                            cmd.Parameters.AddWithValue("@participantId", participantId);
                            cmd.ExecuteNonQuery();
                        }
                    }

                    textBoxParticipantName.Text = "";
                    textBoxParticipantPhone.Text = "";
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
                    MessageBox.Show(@"Selectati un participant");
                    return;
                }

                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
                int participantId = (int)selectedRow.Cells["id_participant"].Value;

                string updatedParticipantName = textBoxParticipantName.Text;
                string updatedParticipantPhone = textBoxParticipantPhone.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "UPDATE Participant SET nume_participant = @participantName, telefon_participant = @participantPhone WHERE id_participant = @participantId",
                            conn);
                    cmd.Parameters.AddWithValue("@participantName", updatedParticipantName);
                    cmd.Parameters.AddWithValue("@participantPhone", updatedParticipantPhone);
                    cmd.Parameters.AddWithValue("@participantId", participantId);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Participant actualizat!");
                textBoxParticipantName.Text = "";
                textBoxParticipantPhone.Text = "";
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
                if (string.IsNullOrWhiteSpace(textBoxEventID.Text))
                {
                    MessageBox.Show(@"Selecteaza un eveniment");
                    return;
                }else if(string.IsNullOrWhiteSpace(textBoxParticipantName.Text) || string.IsNullOrWhiteSpace(textBoxParticipantPhone.Text))
                {
                    MessageBox.Show(@"Completati toate campurile!");
                    return;
                }

                int evenimentId = int.Parse(textBoxEventID.Text);
                string participantName = textBoxParticipantName.Text;
                string participantPhone = textBoxParticipantPhone.Text;

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd =
                        new SqlCommand(
                            "INSERT INTO Participant (id_eveniment, nume_participant, telefon_participant) VALUES (@evenimentId, @participantName, @participantPhone)",
                            conn);
                    cmd.Parameters.AddWithValue("@evenimentId", evenimentId);
                    cmd.Parameters.AddWithValue("@participantName", participantName);
                    cmd.Parameters.AddWithValue("@participantPhone", participantPhone);
                    cmd.ExecuteNonQuery();
                }

                MessageBox.Show(@"Participant adaugat");
                textBoxParticipantName.Text = "";
                textBoxParticipantPhone.Text = "";
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

                string participantName = selectedRow.Cells["nume_participant"].Value.ToString();
                string participantPhone = selectedRow.Cells["telefon_participant"].Value.ToString();

                textBoxParticipantName.Text = participantName;
                textBoxParticipantPhone.Text = participantPhone;
            }
        }

        private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridViewParent.SelectedRows[0];


                int evenimentId = (int)selectedRow.Cells["id_eveniment"].Value;

                textBoxEventID.Text = evenimentId.ToString();
                textBoxParticipantName.Text = "";
                textBoxParticipantPhone.Text = "";
            }
        }
    }
}