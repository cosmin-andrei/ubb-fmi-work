using System;
using System.Drawing;
using System.Windows.Forms;

namespace Cofetarie
{
    partial class Form1
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
            textBoxEventID = new TextBox();
            textBoxBriosaName = new TextBox();
            buttonDelete = new Button();
            buttonUpdate = new Button();
            labelEventID = new Label();
            labelParticipantName = new Label();
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
            dataGridViewParent.Size = new Size(909, 321);
            dataGridViewParent.TabIndex = 0;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(14, 481);
            dataGridViewChild.Margin = new Padding(4, 6, 4, 6);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.Size = new Size(909, 321);
            dataGridViewChild.TabIndex = 1;
            // 
            // labelParent
            // 
            labelParent.AutoSize = true;
            labelParent.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            labelParent.ForeColor = Color.Firebrick;
            labelParent.Location = new Point(14, 35);
            labelParent.Margin = new Padding(4, 0, 4, 0);
            labelParent.Name = "labelParent";
            labelParent.Size = new Size(152, 32);
            labelParent.TabIndex = 2;
            labelParent.Text = "Laboratoare";
            // 
            // labelChild
            // 
            labelChild.AutoSize = true;
            labelChild.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            labelChild.ForeColor = Color.RoyalBlue;
            labelChild.Location = new Point(14, 435);
            labelChild.Margin = new Padding(4, 0, 4, 0);
            labelChild.Name = "labelChild";
            labelChild.Size = new Size(85, 32);
            labelChild.TabIndex = 3;
            labelChild.Text = "Briose";
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
            // textBoxEventID
            // 
            textBoxEventID.Location = new Point(1062, 81);
            textBoxEventID.Margin = new Padding(4, 6, 4, 6);
            textBoxEventID.Name = "textBoxEventID";
            textBoxEventID.Size = new Size(331, 31);
            textBoxEventID.TabIndex = 0;
            // 
            // textBoxParticipantName
            // 
            textBoxBriosaName.Location = new Point(1062, 159);
            textBoxBriosaName.Margin = new Padding(4, 6, 4, 6);
            textBoxBriosaName.Name = "textBoxBriosaName";
            textBoxBriosaName.Size = new Size(331, 31);
            textBoxBriosaName.TabIndex = 1;
            // 
            // buttonDelete
            // 
            buttonDelete.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonDelete.ForeColor = Color.Black;
            buttonDelete.Location = new Point(1062, 215);
            buttonDelete.Margin = new Padding(4, 6, 4, 6);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(156, 44);
            buttonDelete.TabIndex = 3;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = true;
            // 
            // buttonUpdate
            // 
            buttonUpdate.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            buttonUpdate.ForeColor = Color.Black;
            buttonUpdate.Location = new Point(1226, 215);
            buttonUpdate.Margin = new Padding(4, 6, 4, 6);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(167, 44);
            buttonUpdate.TabIndex = 4;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = true;
            // 
            // labelEventID
            // 
            labelEventID.AutoSize = true;
            labelEventID.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            labelEventID.Location = new Point(932, 76);
            labelEventID.Margin = new Padding(4, 0, 4, 0);
            labelEventID.Name = "labelEventID";
            labelEventID.Size = new Size(130, 28);
            labelEventID.TabIndex = 5;
            labelEventID.Text = "Laborator ID:";
            // 
            // labelParticipantName
            // 
            labelParticipantName.AutoSize = true;
            labelParticipantName.Font = new Font("Segoe UI Semibold", 10F, FontStyle.Bold, GraphicsUnit.Point);
            labelParticipantName.Location = new Point(957, 154);
            labelParticipantName.Margin = new Padding(4, 0, 4, 0);
            labelParticipantName.Name = "labelParticipantName";
            labelParticipantName.Size = new Size(71, 28);
            labelParticipantName.TabIndex = 6;
            labelParticipantName.Text = "Name:";
            // 
            // buttonAdd
            // 
            buttonAdd.Font = new Font("Segoe UI", 10F, FontStyle.Bold, GraphicsUnit.Point);
            buttonAdd.ForeColor = Color.ForestGreen;
            buttonAdd.Location = new Point(1062, 283);
            buttonAdd.Margin = new Padding(4, 6, 4, 6);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(331, 44);
            buttonAdd.TabIndex = 8;
            buttonAdd.Text = "Add briosa";
            buttonAdd.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1420, 844);
            Controls.Add(textBoxEventID);
            Controls.Add(textBoxBriosaName);
            Controls.Add(buttonDelete);
            Controls.Add(buttonUpdate);
            Controls.Add(labelEventID);
            Controls.Add(labelParticipantName);
            Controls.Add(buttonAdd);
            Controls.Add(buttonRefresh);
            Controls.Add(labelChild);
            Controls.Add(labelParent);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Margin = new Padding(4, 6, 4, 6);
            Name = "Form1";
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
        private TextBox textBoxEventID;
        private TextBox textBoxBriosaName;

        // Declarațiile pentru butoane
        private Button buttonDelete;
        private Button buttonUpdate;
        private Button buttonAdd;
        private Label labelEventID;
        private Label labelParticipantName;
    }


}

