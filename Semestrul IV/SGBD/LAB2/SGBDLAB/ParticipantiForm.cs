using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Windows.Forms;

namespace SGBDLAB
{
    public partial class ParticipantiForm : Form
    {
        
        //date din fisierul config
        string _connectionString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;

        string parentTable = ConfigurationManager.AppSettings["parentTable"];
        string childTable = ConfigurationManager.AppSettings["childTable"];
        static int childNrOfColumns = int.Parse(ConfigurationManager.AppSettings["childNrOfColumns"]);

        string childColumnNames = ConfigurationManager.AppSettings["childColumnNames"];
        static string childColumnTypes = ConfigurationManager.AppSettings["childColumnTypes"];

        string insertQuerry = ConfigurationManager.AppSettings["insertChild"];
        string updateQuerry = ConfigurationManager.AppSettings["updateChild"];
        
        string childArgs = ConfigurationManager.AppSettings["childArgs"];


        //adaptor = interogari sql, preluam date din DB
        //date pentru UI
        DataSet _ds = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        TextBox[] textBoxes = new TextBox[childNrOfColumns];
        Label[] labels = new Label[childNrOfColumns];
        
        public ParticipantiForm()
        {
            InitializeComponent();
            
            //initializare labels si textboxes
            string[] names = childColumnNames.Split(',');
            for (int i = 0; i < childNrOfColumns; i++)
            {
                labels[i] = new Label();
                textBoxes[i] = new TextBox();
        
                //setare pozitie + nume
                labels[i].Text = names[i];
                
                //coordonate X, Y, in pixeli
                labels[i].Location = new Point(i * 175, 340);
        
                textBoxes[i].Text = "";
                textBoxes[i].Location = new Point(i * 175, 360); 
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            
            //adaug propriu-zis campurile in form
            for(int i = 0; i < childNrOfColumns; i++)
            {
                Controls.Add(labels[i]);
                Controls.Add(textBoxes[i]);
            }
            
            try
            {
                //deschid conexiunea cu DB
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    //initializare adaptoare pt tabele
                    //adaptor = interogari sql, preluam date din DB

                    string selectParent = ConfigurationManager.AppSettings["selectParent"];
                    string selectChild = ConfigurationManager.AppSettings["selectChild"];

                    _parentAdapter = new SqlDataAdapter(selectParent, conn);
                    _childAdapter = new SqlDataAdapter(selectChild, conn);
                    _parentAdapter.Fill(_ds, parentTable);
                    _childAdapter.Fill(_ds, childTable);

                    string parentPK = ConfigurationManager.AppSettings["parentPK"];
                    string childFK = ConfigurationManager.AppSettings["childFK"];

                    //definesc relatia dintre tabele (PK, FK)
                    DataColumn pkColumn = _ds.Tables[parentTable].Columns[parentPK];
                    DataColumn fkColumn = _ds.Tables[childTable].Columns[childFK];
                    DataRelation relation = new DataRelation("FK_Parent_Child", pkColumn, fkColumn);
                    _ds.Relations.Add(relation);

                    //BindingSource = conectam datele intre UI (DataGridView) si Dataset
                    _bsParent = new BindingSource();
                    _bsChild = new BindingSource();
                    _bsParent.DataSource = _ds.Tables[parentTable];
                    dataGridViewParent.DataSource = _bsParent;
                    _bsChild.DataSource = _bsParent;
                    _bsChild.DataMember = "FK_Parent_Child";
                    dataGridViewChild.DataSource = _bsChild;

                    //setare readOnly pt id
                    textBoxes[0].ReadOnly = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.Message);
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

                    _ds.Tables[childTable].Clear();
                    _ds.Tables[parentTable].Clear();
                    

                    _parentAdapter.Fill(_ds, parentTable);
                    _childAdapter.Fill(_ds, childTable);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Console.WriteLine(ex.ToString());
            }
        }

        private void buttonDelete_Click_1(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 0)
            {
                MessageBox.Show(@"Selecteaza un rand!");
            }
            else if (dataGridViewChild.SelectedRows.Count > 1)
            {
                MessageBox.Show(@"Un singur rand!");
            }
            else
                try
                {
                    //extragere rand + id
                    DataGridViewRow selectedRow = dataGridViewChild.CurrentRow;
                    if (selectedRow != null)
                    {
                        string childPK = ConfigurationManager.AppSettings["childPK"];
                        int id = (int)selectedRow.Cells[childPK].Value;

                        using (SqlConnection conn = new SqlConnection(_connectionString))
                        {
                            conn.Open();
                            string deleteQuery = "DELETE FROM " + childTable + " WHERE " + childPK + " = @id";
                            SqlCommand cmd = new SqlCommand(deleteQuery, conn);
                            cmd.Parameters.AddWithValue("@id", id);
                            cmd.ExecuteNonQuery();
                        }
                    }
            
                    MessageBox.Show(@"Sters cu succes!");
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
                    MessageBox.Show(@"Selectati un rand");
                    return;
                }

                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
                int id = (int)selectedRow.Cells[ConfigurationManager.AppSettings["childPK"]].Value;


                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd = new SqlCommand(updateQuerry, conn);
                    cmd.Parameters.AddWithValue("@id", id);

                    string[] args = childArgs.Split(Convert.ToChar(","));
                    string[] types = childColumnTypes.Split(Convert.ToChar(","));
                    for (int i = 0; i < childNrOfColumns; i++)
                    {
                        string arg = args[i];
                        string type = types[i]; 

                        if (type == "int")
                        {
                            cmd.Parameters.Add(arg, SqlDbType.Int).Value = int.Parse(textBoxes[i].Text);
                        }
                        else if (type == "string")
                        {
                            cmd.Parameters.Add(arg, SqlDbType.VarChar).Value = textBoxes[i].Text;
                        }
                        else if (type == "float")
                        {
                            cmd.Parameters.Add(arg, SqlDbType.Float).Value = float.Parse(textBoxes[i].Text);
                        }
                    }


                    cmd.ExecuteNonQuery();
                    
                    conn.Close();
                }
                
                MessageBox.Show(@"Actualizat cu succes!");
                buttonRefresh_Click();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonAdd_Click_1(object sender, EventArgs e)
        {
            try
            {
                for (int i = 0; i < childNrOfColumns; i++)
                {
                    if (textBoxes[i].Text == "")
                    {
                        MessageBox.Show(@"Completati toate campurile!");
                        return;
                    }
                }

                string[] args = childArgs.Split(Convert.ToChar(","));
                string[] types = childColumnTypes.Split(Convert.ToChar(","));

                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    conn.Open();
                    SqlCommand cmd = new SqlCommand(insertQuerry, conn);
                    for (int i = 0; i < childNrOfColumns; i++)
                    {
                        string type = types[i];
                        if (type == "int")
                        {
                            cmd.Parameters.Add(args[i], SqlDbType.Int).Value = int.Parse(textBoxes[i].Text);
                        }
                        else if (type == "string")
                        {
                            cmd.Parameters.Add(args[i], SqlDbType.VarChar).Value = textBoxes[i].Text;
                        }
                    }

                    cmd.ExecuteNonQuery();
                    MessageBox.Show(@"Adaugat cu succes!");
                    conn.Close();
                }
                
                buttonRefresh_Click();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                MessageBox.Show(ex.Message);
            }
        }


        private void dataGridViewChild_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedRows.Count == 1)
            {
                DataGridViewRow selectedRow = dataGridViewChild.SelectedRows[0];
        
                for(int i=0; i<childNrOfColumns; i++)
                {
                    textBoxes[i].Text = selectedRow.Cells[i+1].Value.ToString();
                }
            }
        }
        
        private void dataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridViewParent.SelectedRows[0];
        
        
                int parentID = (int)selectedRow.Cells[ConfigurationManager.AppSettings["parentPK"]].Value;

                textBoxes[0].Text = parentID.ToString();
                
                for(int i=1; i<childNrOfColumns; i++)
                {
                    textBoxes[i].Text = "";
                }
                
            }
        }
        
    }
}