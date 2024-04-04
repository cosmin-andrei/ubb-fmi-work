using System;
using System.Drawing;
using System.Windows.Forms;

namespace SGBDLAB
{
    partial class ParticipantiForm
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
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.labelParent = new System.Windows.Forms.Label();
            this.labelChild = new System.Windows.Forms.Label();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.textBoxEventID = new System.Windows.Forms.TextBox();
            this.textBoxParticipantName = new System.Windows.Forms.TextBox();
            this.textBoxParticipantPhone = new System.Windows.Forms.TextBox();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonUpdate = new System.Windows.Forms.Button();
            this.labelEventID = new System.Windows.Forms.Label();
            this.labelParticipantName = new System.Windows.Forms.Label();
            this.labelParticipantPhone = new System.Windows.Forms.Label();
            this.buttonAdd = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(13, 65);
            this.dataGridViewParent.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.RowHeadersWidth = 51;
            this.dataGridViewParent.Size = new System.Drawing.Size(818, 257);
            this.dataGridViewParent.TabIndex = 0;
            this.dataGridViewParent.SelectionChanged += new System.EventHandler(this.dataGridViewParent_SelectionChanged);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(13, 385);
            this.dataGridViewChild.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.RowHeadersWidth = 51;
            this.dataGridViewChild.Size = new System.Drawing.Size(818, 257);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.SelectionChanged += new System.EventHandler(this.dataGridViewChild_SelectionChanged);
            // 
            // labelParent
            // 
            this.labelParent.AutoSize = true;
            this.labelParent.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelParent.ForeColor = System.Drawing.Color.Firebrick;
            this.labelParent.Location = new System.Drawing.Point(13, 28);
            this.labelParent.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelParent.Name = "labelParent";
            this.labelParent.Size = new System.Drawing.Size(89, 32);
            this.labelParent.TabIndex = 2;
            this.labelParent.Text = "Events";
            // 
            // labelChild
            // 
            this.labelChild.AutoSize = true;
            this.labelChild.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelChild.ForeColor = System.Drawing.Color.RoyalBlue;
            this.labelChild.Location = new System.Drawing.Point(13, 348);
            this.labelChild.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelChild.Name = "labelChild";
            this.labelChild.Size = new System.Drawing.Size(151, 32);
            this.labelChild.TabIndex = 3;
            this.labelChild.Text = "Participants";
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.buttonRefresh.ForeColor = System.Drawing.Color.DodgerBlue;
            this.buttonRefresh.Location = new System.Drawing.Point(1116, 385);
            this.buttonRefresh.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(138, 35);
            this.buttonRefresh.TabIndex = 4;
            this.buttonRefresh.Text = "Refresh Data";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            // 
            // textBoxEventID
            // 
            this.textBoxEventID.Location = new System.Drawing.Point(956, 65);
            this.textBoxEventID.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textBoxEventID.Name = "textBoxEventID";
            this.textBoxEventID.Size = new System.Drawing.Size(298, 26);
            this.textBoxEventID.TabIndex = 0;
            // 
            // textBoxParticipantName
            // 
            this.textBoxParticipantName.Location = new System.Drawing.Point(956, 127);
            this.textBoxParticipantName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textBoxParticipantName.Name = "textBoxParticipantName";
            this.textBoxParticipantName.Size = new System.Drawing.Size(298, 26);
            this.textBoxParticipantName.TabIndex = 1;
            // 
            // textBoxParticipantPhone
            // 
            this.textBoxParticipantPhone.Location = new System.Drawing.Point(956, 189);
            this.textBoxParticipantPhone.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textBoxParticipantPhone.Name = "textBoxParticipantPhone";
            this.textBoxParticipantPhone.Size = new System.Drawing.Size(298, 26);
            this.textBoxParticipantPhone.TabIndex = 2;
            // 
            // buttonDelete
            // 
            this.buttonDelete.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.buttonDelete.ForeColor = System.Drawing.Color.Black;
            this.buttonDelete.Location = new System.Drawing.Point(956, 236);
            this.buttonDelete.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(140, 35);
            this.buttonDelete.TabIndex = 3;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click_1);
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.buttonUpdate.ForeColor = System.Drawing.Color.Black;
            this.buttonUpdate.Location = new System.Drawing.Point(1104, 236);
            this.buttonUpdate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(150, 35);
            this.buttonUpdate.TabIndex = 4;
            this.buttonUpdate.Text = "Update";
            this.buttonUpdate.UseVisualStyleBackColor = true;
            this.buttonUpdate.Click += new System.EventHandler(this.buttonUpdate_Click_1);
            // 
            // labelEventID
            // 
            this.labelEventID.AutoSize = true;
            this.labelEventID.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelEventID.Location = new System.Drawing.Point(839, 61);
            this.labelEventID.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelEventID.Name = "labelEventID";
            this.labelEventID.Size = new System.Drawing.Size(93, 28);
            this.labelEventID.TabIndex = 5;
            this.labelEventID.Text = "Event ID:";
            // 
            // labelParticipantName
            // 
            this.labelParticipantName.AutoSize = true;
            this.labelParticipantName.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelParticipantName.Location = new System.Drawing.Point(861, 123);
            this.labelParticipantName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelParticipantName.Name = "labelParticipantName";
            this.labelParticipantName.Size = new System.Drawing.Size(71, 28);
            this.labelParticipantName.TabIndex = 6;
            this.labelParticipantName.Text = "Name:";
            // 
            // labelParticipantPhone
            // 
            this.labelParticipantPhone.AutoSize = true;
            this.labelParticipantPhone.Font = new System.Drawing.Font("Segoe UI Semibold", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelParticipantPhone.Location = new System.Drawing.Point(856, 185);
            this.labelParticipantPhone.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelParticipantPhone.Name = "labelParticipantPhone";
            this.labelParticipantPhone.Size = new System.Drawing.Size(76, 28);
            this.labelParticipantPhone.TabIndex = 7;
            this.labelParticipantPhone.Text = "Phone:";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.buttonAdd.ForeColor = System.Drawing.Color.ForestGreen;
            this.buttonAdd.Location = new System.Drawing.Point(956, 284);
            this.buttonAdd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(298, 35);
            this.buttonAdd.TabIndex = 8;
            this.buttonAdd.Text = "Add participant";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click_1);
            // 
            // ParticipantiForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1278, 675);
            this.Controls.Add(this.textBoxEventID);
            this.Controls.Add(this.textBoxParticipantName);
            this.Controls.Add(this.textBoxParticipantPhone);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonUpdate);
            this.Controls.Add(this.labelEventID);
            this.Controls.Add(this.labelParticipantName);
            this.Controls.Add(this.labelParticipantPhone);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.labelChild);
            this.Controls.Add(this.labelParent);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "ParticipantiForm";
            this.Text = "ParticipantiForm";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Label labelParent;
        private System.Windows.Forms.Label labelChild;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.TextBox textBoxEventID;
        private System.Windows.Forms.TextBox textBoxParticipantName;
        private System.Windows.Forms.TextBox textBoxParticipantPhone;

        // Declarațiile pentru butoane
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonUpdate;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Label labelEventID;
        private System.Windows.Forms.Label labelParticipantName;
        private System.Windows.Forms.Label labelParticipantPhone;
    }


}

