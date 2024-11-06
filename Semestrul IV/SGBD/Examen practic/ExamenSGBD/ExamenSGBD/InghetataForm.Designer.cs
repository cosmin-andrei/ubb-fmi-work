using System;
using System.Drawing;
using System.Windows.Forms;

namespace ExamenSGBD
{
    partial class InghetataForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

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
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            labelParent = new Label();
            labelChild = new Label();
            buttonRefresh = new Button();
            textBoxTipID = new TextBox();
            textBoxDenumire = new TextBox();
            buttonDelete = new Button();
            buttonUpdate = new Button();
            labelProducatorID = new Label();
            labelBiscuitiName = new Label();
            buttonAdd = new Button();
            textBoxPret = new TextBox();
            label1 = new Label();
            textBoxGramaj = new TextBox();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(14, 81);
            dataGridViewParent.Margin = new Padding(4, 6, 4, 6);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.Size = new Size(849, 321);
            dataGridViewParent.TabIndex = 0;
            dataGridViewParent.SelectionChanged += dataGridViewParent_SelectionChanged;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(14, 481);
            dataGridViewChild.Margin = new Padding(4, 6, 4, 6);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.Size = new Size(849, 321);
            dataGridViewChild.TabIndex = 1;
            dataGridViewChild.SelectionChanged += dataGridViewChild_SelectionChanged;
            // 
            // labelParent
            // 
            labelParent.AutoSize = true;
            labelParent.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            labelParent.ForeColor = Color.Firebrick;
            labelParent.Location = new Point(14, 35);
            labelParent.Margin = new Padding(4, 0, 4, 0);
            labelParent.Name = "labelParent";
            labelParent.Size = new Size(197, 32);
            labelParent.TabIndex = 2;
            labelParent.Text = "Tipuri inghetate";
            // 
            // labelChild
            // 
            labelChild.AutoSize = true;
            labelChild.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            labelChild.ForeColor = Color.RoyalBlue;
            labelChild.Location = new Point(14, 435);
            labelChild.Margin = new Padding(4, 0, 4, 0);
            labelChild.Name = "labelChild";
            labelChild.Size = new Size(123, 32);
            labelChild.TabIndex = 3;
            labelChild.Text = "Inghetate";
            // 
            // buttonRefresh
            // 
            buttonRefresh.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonRefresh.ForeColor = Color.DodgerBlue;
            buttonRefresh.Location = new Point(1241, 758);
            buttonRefresh.Margin = new Padding(4, 6, 4, 6);
            buttonRefresh.Name = "buttonRefresh";
            buttonRefresh.Size = new Size(153, 44);
            buttonRefresh.TabIndex = 4;
            buttonRefresh.Text = "Refresh Data";
            buttonRefresh.UseVisualStyleBackColor = true;
            // 
            // textBoxTipID
            // 
            textBoxTipID.Location = new Point(1062, 81);
            textBoxTipID.Margin = new Padding(4, 6, 4, 6);
            textBoxTipID.Name = "textBoxTipID";
            textBoxTipID.Size = new Size(331, 31);
            textBoxTipID.TabIndex = 0;
            // 
            // textBoxDenumire
            // 
            textBoxDenumire.Location = new Point(1062, 139);
            textBoxDenumire.Margin = new Padding(4, 6, 4, 6);
            textBoxDenumire.Name = "textBoxDenumire";
            textBoxDenumire.Size = new Size(331, 31);
            textBoxDenumire.TabIndex = 1;
            // 
            // buttonDelete
            // 
            buttonDelete.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonDelete.ForeColor = Color.Black;
            buttonDelete.Location = new Point(973, 346);
            buttonDelete.Margin = new Padding(4, 6, 4, 6);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(156, 44);
            buttonDelete.TabIndex = 3;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = true;
            buttonDelete.Click += buttonDelete_Click_1;
            // 
            // buttonUpdate
            // 
            buttonUpdate.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonUpdate.ForeColor = Color.Black;
            buttonUpdate.Location = new Point(1226, 346);
            buttonUpdate.Margin = new Padding(4, 6, 4, 6);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(167, 44);
            buttonUpdate.TabIndex = 4;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = true;
            buttonUpdate.Click += buttonUpdate_Click_1;
            // 
            // labelProducatorID
            // 
            labelProducatorID.AutoSize = true;
            labelProducatorID.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            labelProducatorID.ImageAlign = ContentAlignment.TopCenter;
            labelProducatorID.Location = new Point(891, 81);
            labelProducatorID.Margin = new Padding(4, 0, 4, 0);
            labelProducatorID.Name = "labelProducatorID";
            labelProducatorID.Size = new Size(163, 28);
            labelProducatorID.TabIndex = 5;
            labelProducatorID.Text = "Tip inghetata ID:";
            // 
            // labelBiscuitiName
            // 
            labelBiscuitiName.AutoSize = true;
            labelBiscuitiName.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            labelBiscuitiName.Location = new Point(947, 139);
            labelBiscuitiName.Margin = new Padding(4, 0, 4, 0);
            labelBiscuitiName.Name = "labelBiscuitiName";
            labelBiscuitiName.Size = new Size(107, 28);
            labelBiscuitiName.TabIndex = 6;
            labelBiscuitiName.Text = "Denumire:";
            // 
            // buttonAdd
            // 
            buttonAdd.Font = new Font("Segoe UI", 10F, FontStyle.Bold, GraphicsUnit.Point);
            buttonAdd.ForeColor = Color.ForestGreen;
            buttonAdd.Location = new Point(973, 402);
            buttonAdd.Margin = new Padding(4, 6, 4, 6);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(420, 44);
            buttonAdd.TabIndex = 8;
            buttonAdd.Text = "Add inghetata";
            buttonAdd.UseVisualStyleBackColor = true;
            buttonAdd.Click += buttonAdd_Click_1;
            // 
            // textBoxPret
            // 
            textBoxPret.Location = new Point(1062, 207);
            textBoxPret.Margin = new Padding(4, 6, 4, 6);
            textBoxPret.Name = "textBoxPret";
            textBoxPret.Size = new Size(331, 31);
            textBoxPret.TabIndex = 9;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(1000, 207);
            label1.Margin = new Padding(4, 0, 4, 0);
            label1.Name = "label1";
            label1.Size = new Size(54, 28);
            label1.TabIndex = 10;
            label1.Text = "Pret:";
            // 
            // textBoxGramaj
            // 
            textBoxGramaj.Location = new Point(1062, 275);
            textBoxGramaj.Margin = new Padding(4, 6, 4, 6);
            textBoxGramaj.Name = "textBoxGramaj";
            textBoxGramaj.Size = new Size(331, 31);
            textBoxGramaj.TabIndex = 11;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(973, 275);
            label2.Margin = new Padding(4, 0, 4, 0);
            label2.Name = "label2";
            label2.Size = new Size(81, 28);
            label2.TabIndex = 12;
            label2.Text = "Gramaj:";
            // 
            // InghetataForm
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1420, 844);
            Controls.Add(label2);
            Controls.Add(textBoxGramaj);
            Controls.Add(label1);
            Controls.Add(textBoxPret);
            Controls.Add(textBoxTipID);
            Controls.Add(textBoxDenumire);
            Controls.Add(buttonDelete);
            Controls.Add(buttonUpdate);
            Controls.Add(labelProducatorID);
            Controls.Add(labelBiscuitiName);
            Controls.Add(buttonAdd);
            Controls.Add(buttonRefresh);
            Controls.Add(labelChild);
            Controls.Add(labelParent);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Margin = new Padding(4, 6, 4, 6);
            Name = "InghetataForm";
            Text = "ParticipantiForm";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewChild;
        private Label labelParent;
        private Label labelChild;
        private Button buttonRefresh;
        private TextBox textBoxTipID;
        private TextBox textBoxDenumire;

        // Declarațiile pentru butoane
        private Button buttonDelete;
        private Button buttonUpdate;
        private Button buttonAdd;
        private Label labelProducatorID;
        private Label labelBiscuitiName;
        private TextBox textBoxPret;
        private Label label1;
        private TextBox textBoxGramaj;
        private Label label2;
    }


}

