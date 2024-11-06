using System;
using System.Drawing;
using System.Windows.Forms;

namespace Biscuiti
{
    partial class BiscuitiForm
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
            textBoxProducatorID = new TextBox();
            textBoxBiscuitiName = new TextBox();
            buttonDelete = new Button();
            buttonUpdate = new Button();
            labelProducatorID = new Label();
            labelBiscuitiName = new Label();
            buttonAdd = new Button();
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
            labelParent.Size = new Size(150, 32);
            labelParent.TabIndex = 2;
            labelParent.Text = "Producatori";
            // 
            // labelChild
            // 
            labelChild.AutoSize = true;
            labelChild.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            labelChild.ForeColor = Color.RoyalBlue;
            labelChild.Location = new Point(14, 435);
            labelChild.Margin = new Padding(4, 0, 4, 0);
            labelChild.Name = "labelChild";
            labelChild.Size = new Size(97, 32);
            labelChild.TabIndex = 3;
            labelChild.Text = "Biscuiti";
            // 
            // buttonRefresh
            // 
            buttonRefresh.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonRefresh.ForeColor = Color.DodgerBlue;
            buttonRefresh.Location = new Point(1240, 481);
            buttonRefresh.Margin = new Padding(4, 6, 4, 6);
            buttonRefresh.Name = "buttonRefresh";
            buttonRefresh.Size = new Size(153, 44);
            buttonRefresh.TabIndex = 4;
            buttonRefresh.Text = "Refresh Data";
            buttonRefresh.UseVisualStyleBackColor = true;
            // 
            // textBoxProducatorID
            // 
            textBoxProducatorID.Location = new Point(1062, 81);
            textBoxProducatorID.Margin = new Padding(4, 6, 4, 6);
            textBoxProducatorID.Name = "textBoxProducatorID";
            textBoxProducatorID.Size = new Size(331, 31);
            textBoxProducatorID.TabIndex = 0;
            // 
            // textBoxBiscuitiName
            // 
            textBoxBiscuitiName.Location = new Point(1062, 159);
            textBoxBiscuitiName.Margin = new Padding(4, 6, 4, 6);
            textBoxBiscuitiName.Name = "textBoxBiscuitiName";
            textBoxBiscuitiName.Size = new Size(331, 31);
            textBoxBiscuitiName.TabIndex = 1;
            // 
            // buttonDelete
            // 
            buttonDelete.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonDelete.ForeColor = Color.Black;
            buttonDelete.Location = new Point(1062, 219);
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
            buttonUpdate.Location = new Point(1227, 219);
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
            labelProducatorID.Location = new Point(912, 80);
            labelProducatorID.Margin = new Padding(4, 0, 4, 0);
            labelProducatorID.Name = "labelProducatorID";
            labelProducatorID.Size = new Size(143, 28);
            labelProducatorID.TabIndex = 5;
            labelProducatorID.Text = "Producator ID:";
            // 
            // labelBiscuitiName
            // 
            labelBiscuitiName.AutoSize = true;
            labelBiscuitiName.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            labelBiscuitiName.Location = new Point(919, 159);
            labelBiscuitiName.Margin = new Padding(4, 0, 4, 0);
            labelBiscuitiName.Name = "labelBiscuitiName";
            labelBiscuitiName.Size = new Size(143, 28);
            labelBiscuitiName.TabIndex = 6;
            labelBiscuitiName.Text = "Nume biscuiti:";
            // 
            // buttonAdd
            // 
            buttonAdd.Font = new Font("Segoe UI", 10F, FontStyle.Bold, GraphicsUnit.Point);
            buttonAdd.ForeColor = Color.ForestGreen;
            buttonAdd.Location = new Point(1062, 280);
            buttonAdd.Margin = new Padding(4, 6, 4, 6);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(331, 44);
            buttonAdd.TabIndex = 8;
            buttonAdd.Text = "Add Biscuite";
            buttonAdd.UseVisualStyleBackColor = true;
            buttonAdd.Click += buttonAdd_Click_1;
            // 
            // BiscuitiForm
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1420, 844);
            Controls.Add(textBoxProducatorID);
            Controls.Add(textBoxBiscuitiName);
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
            Name = "BiscuitiForm";
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
        private TextBox textBoxProducatorID;
        private TextBox textBoxBiscuitiName;

        // Declarațiile pentru butoane
        private Button buttonDelete;
        private Button buttonUpdate;
        private Button buttonAdd;
        private Label labelProducatorID;
        private Label labelBiscuitiName;
    }


}

