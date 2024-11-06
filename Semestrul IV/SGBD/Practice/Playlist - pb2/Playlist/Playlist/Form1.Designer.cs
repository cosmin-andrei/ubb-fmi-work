namespace Playlist;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
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
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        listBoxParent = new ListBox();
        dataGridViewChild = new DataGridView();
        RefreshData_button = new Button();
        label1 = new Label();
        label2 = new Label();
        idArtist_textBox = new TextBox();
        numeMel_textBox = new TextBox();
        addButton = new Button();
        updateButton = new Button();
        deleteButton = new Button();
        ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
        SuspendLayout();
        // 
        // listBoxParent
        // 
        listBoxParent.FormattingEnabled = true;
        listBoxParent.ItemHeight = 25;
        listBoxParent.Location = new Point(12, 12);
        listBoxParent.Name = "listBoxParent";
        listBoxParent.Size = new Size(432, 129);
        listBoxParent.TabIndex = 0;
        listBoxParent.SelectedIndexChanged += listBoxParent_SelectedIndexChanged;
        // 
        // dataGridViewChild
        // 
        dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        dataGridViewChild.Location = new Point(12, 163);
        dataGridViewChild.Name = "dataGridViewChild";
        dataGridViewChild.RowHeadersWidth = 62;
        dataGridViewChild.RowTemplate.Height = 33;
        dataGridViewChild.Size = new Size(432, 225);
        dataGridViewChild.TabIndex = 1;
        dataGridViewChild.CellContentClick += dataGridViewChild_CellContentClick;
        // 
        // RefreshData_button
        // 
        RefreshData_button.Location = new Point(486, 319);
        RefreshData_button.Name = "RefreshData_button";
        RefreshData_button.Size = new Size(253, 57);
        RefreshData_button.TabIndex = 2;
        RefreshData_button.Text = "Refresh data";
        RefreshData_button.UseVisualStyleBackColor = true;
        RefreshData_button.Click += RefreshData_button_Click;
        // 
        // label1
        // 
        label1.AutoSize = true;
        label1.Location = new Point(486, 34);
        label1.Name = "label1";
        label1.Size = new Size(77, 25);
        label1.TabIndex = 3;
        label1.Text = "ID Artist";
        // 
        // label2
        // 
        label2.AutoSize = true;
        label2.Location = new Point(486, 80);
        label2.Name = "label2";
        label2.Size = new Size(76, 25);
        label2.TabIndex = 4;
        label2.Text = "Melodie";
        // 
        // idArtist_textBox
        // 
        idArtist_textBox.Location = new Point(574, 34);
        idArtist_textBox.Name = "idArtist_textBox";
        idArtist_textBox.Size = new Size(165, 31);
        idArtist_textBox.TabIndex = 5;
        // 
        // numeMel_textBox
        // 
        numeMel_textBox.Location = new Point(574, 77);
        numeMel_textBox.Name = "numeMel_textBox";
        numeMel_textBox.Size = new Size(165, 31);
        numeMel_textBox.TabIndex = 6;
        // 
        // addButton
        // 
        addButton.Location = new Point(486, 124);
        addButton.Name = "addButton";
        addButton.Size = new Size(127, 34);
        addButton.TabIndex = 7;
        addButton.Text = "Add";
        addButton.UseVisualStyleBackColor = true;
        addButton.Click += button2_Click;
        // 
        // updateButton
        // 
        updateButton.Location = new Point(619, 124);
        updateButton.Name = "updateButton";
        updateButton.Size = new Size(120, 34);
        updateButton.TabIndex = 8;
        updateButton.Text = "Update";
        updateButton.UseVisualStyleBackColor = true;
        updateButton.Click += button3_Click;
        // 
        // deleteButton
        // 
        deleteButton.Location = new Point(486, 174);
        deleteButton.Name = "deleteButton";
        deleteButton.Size = new Size(253, 30);
        deleteButton.TabIndex = 9;
        deleteButton.Text = "Delete";
        deleteButton.UseVisualStyleBackColor = true;
        deleteButton.Click += deleteButton_Click;
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(10F, 25F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(793, 414);
        Controls.Add(deleteButton);
        Controls.Add(updateButton);
        Controls.Add(addButton);
        Controls.Add(numeMel_textBox);
        Controls.Add(idArtist_textBox);
        Controls.Add(label2);
        Controls.Add(label1);
        Controls.Add(RefreshData_button);
        Controls.Add(dataGridViewChild);
        Controls.Add(listBoxParent);
        Name = "Form1";
        Text = "Form1";
        Load += Form1_Load;
        ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
        ResumeLayout(false);
        PerformLayout();
    }

    private void RefreshData_button_Click(object sender, EventArgs e)
    {
        throw new NotImplementedException();
    }

    #endregion

    private ListBox listBoxParent;
    private DataGridView dataGridViewChild;
    private Button RefreshData_button;
    private Label label1;
    private Label label2;
    private TextBox idArtist_textBox;
    private TextBox numeMel_textBox;
    private Button addButton;
    private Button updateButton;
    private Button deleteButton;
}