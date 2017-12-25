using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        int current = 1;
        private string first = "F";
        private string r1 = "F";
        private string r2 = "F";
        private string r3 = "F";
        private string r4 = "F";
        private string r5 = "F";
        private string angle = "F";
        private string iteration = "F";
        private string type = "F";

        public Form1()
        {
            InitializeComponent();
            lbl_col1.BackColor = Color.White;
            lbl_col2.BackColor = Color.White;
            lbl_col3.BackColor = Color.White;
        }

        private string ColorToRGB(string c)
        {
            double value = double.Parse(c);
            value = Math.Round(value / 255, 2);

            return value.ToString();
        }

        private void ClearForm()
        {
            txt_FirstSentence.Text = null;
            txt_Rule1.Text = null;
            txt_Rule2.Text = null;
            txt_Rule3.Text = null;
            txt_Rule4.Text = null;
            txt_Rule5.Text = null;
            txt_Rule6.Text = null;
            txt_Angle.Text = null;
            txt_Iteration.Text = null;
            txt_Type.Text = null;

                      
            btn_f1.BorderStyle = BorderStyle.None;
            btn_f2.BorderStyle = BorderStyle.None;
            btn_f3.BorderStyle = BorderStyle.None;
            btn_f4.BorderStyle = BorderStyle.None;
            btn_f5.BorderStyle = BorderStyle.None;
            btn_f6.BorderStyle = BorderStyle.None;
            btn_f7.BorderStyle = BorderStyle.None;
            btn_f8.BorderStyle = BorderStyle.None;
            btn_f9.BorderStyle = BorderStyle.None;
            btn_f10.BorderStyle = BorderStyle.None;
            btn_f11.BorderStyle = BorderStyle.None;
            btn_f12.BorderStyle = BorderStyle.None;
            btn_f13.BorderStyle = BorderStyle.None;
            btn_f14.BorderStyle = BorderStyle.None;
            btn_f15.BorderStyle = BorderStyle.None;
            btn_f16.BorderStyle = BorderStyle.None;
        }

        private void SetForm()
        {
            txt_FirstSentence.Text = first;
            txt_Rule1.Text = r1;
            txt_Rule2.Text = r2;
            txt_Rule3.Text = r3;
            txt_Rule4.Text = r4;
            txt_Rule5.Text = r5;
            txt_Rule6.Text = "F";
            txt_Angle.Text = angle;
            txt_Iteration.Text = iteration;
            txt_Type.Text = type;
        }

        private void SetFormula(PictureBox button)
        {
            ClearForm();

            int id = 1;
            string buttonId = button.Name;

            switch (buttonId)
            {
                case "btn_f1": { id = 1; break; }
                case "btn_f2": { id = 2; break; }
                case "btn_f3": { id = 3; break; }
                case "btn_f4": { id = 4; break; }
                case "btn_f5": { id = 5; break; }
                case "btn_f6": { id = 6; break; }
                case "btn_f7": { id = 7; break; }
                case "btn_f8": { id = 8; break; }

                case "btn_f9": { id = 9; break; }
                case "btn_f10": { id = 10; break; }
                case "btn_f11": { id = 11; break; }
                case "btn_f12": { id = 12; break; }
                case "btn_f13": { id = 13; break; }
                case "btn_f14": { id = 14; break; }
                case "btn_f15": { id = 15; break; }
                case "btn_f16": { id = 16; break; }
            }

            switch (id)
            {
                case 1:
                    {
                        first = "F+F+F+F";
                        r1 = "F+F-F-FF+F+F-F";
                        r2 = "F";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("4");
                        type = ("0");
                        break;
                    }
                case 2:
                    {
                        first = "F+F+F+F";
                        r1 = "FF+F+F+F+FF";
                        r2 = "F";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("4");
                        type = ("0");
                        break;
                    }
                case 3:
                    {
                        first = "F+F+F+F";
                        r1 = "FF+F+F+F+F+F-F";
                        r2 = "F";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("4");
                        type = ("0");
                        break;
                    }
                case 4:
                    {
                        first = "L";
                        r1 = "+RF-LFL-FR+";
                        r2 = "-LF+RFR+FL-";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("7");
                        type = ("1");
                        break;
                    }
                case 5:
                    {
                        first = "L";
                        r1 = "LFRFL+F+RFLFR-F-LFRFL";
                        r2 = "RFLFR-F-LFRFL+F+RFLFR";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("5");
                        type = ("1");
                        break;
                    }
                case 6:
                    {
                        first = "L";
                        r1 = "L+RF+";
                        r2 = "-FL-R";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("90");
                        iteration = ("14");
                        type = ("1");
                        break;
                    }
                case 7:
                    {
                        first = "R";
                        r1 = "R+L+R";
                        r2 = "L-R-L";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("60");
                        iteration = ("7");
                        type = ("2");
                        break;
                    }
                case 8:
                    {
                        first = "R";
                        r1 = "L+R++R-L--LL-R+";
                        r2 = "-L+RR++R+L--L-R";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("60");
                        iteration = ("5");
                        type = ("2");
                        break;
                    }
                case 9:
                    {
                        first = "F";
                        r1 = "F[+F]F[-F]F";
                        r2 = "F";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("25.7");
                        iteration = ("4");
                        type = ("0");
                        break;
                    }
                case 10:
                    {
                        first = "X";
                        r1 = "F[+X]F[-X]+X";
                        r2 = "FF";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("20.7");
                        iteration = ("7");
                        type = ("3");
                        break;
                    }
                case 11:
                    {
                        first = "X";
                        r1 = "F-[[X]+X]+F[+FX]-X";
                        r2 = "FF";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("22.5");
                        iteration = ("5");
                        type = ("3");
                        break;
                    }
                case 12:
                    {
                        first = "X";
                        r1 = "F[+X][-X]FX";
                        r2 = "FF";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("25.7");
                        iteration = ("7");
                        type = ("3");
                        break;
                    }
                case 13:
                    {
                        first = "F";
                        r1 = "FF+[+F-F-F]-[-F+F+F]";
                        r2 = "F";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("22.5");
                        iteration = ("4");
                        type = ("4");
                        break;
                    }
                case 14:
                    {
                        first = "GFX[+G][-G]";
                        r1 = "GFX[+G][-G]";
                        r2 = "X[-FFF][+FFF]FX";
                        r3 = "F";
                        r4 = "F";
                        r5 = "F";
                        angle = ("25.7");
                        iteration = ("5");
                        type = ("6");
                        break;
                    }
                case 15:
                    {
                        first = "SLFFF";
                        r1 = "[+++G][---G]TS";
                        r2 = "+H[-G]L";
                        r3 = "-G[+H]L";
                        r4 = "TL";
                        r5 = "[-FFF][+FFF]F";
                        angle = ("18");
                        iteration = ("9");
                        type = ("7");
                        break;
                    }
                case 16:
                    {
                        first = "T";
                        r1 = "R+[T]--[--L]R[++L]-[T]++T";
                        r2 = "F[--L][++L]F";
                        r3 = "[{+Q-Q-Q+@Q-Q-Q}]";
                        r4 = "Q";
                        r5 = "FF";
                        angle = ("30");
                        iteration = ("5");
                        type = ("8");
                        break;
                    }
            }

            current = id;

            SetForm();

            button.BorderStyle = BorderStyle.Fixed3D;

            
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                this.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SetFormula(btn_f1);
        }

        private void btn_f1_Click(object sender, EventArgs e)
        {
            PictureBox button = (PictureBox)sender;
             SetFormula(button);   
        }

        private void btn_col1_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();

            Button button = (Button)sender;
            string buttonId = button.Name;

            if (buttonId.Equals("btn_col1"))
            { lbl_col1.BackColor = colorDialog1.Color; }
            else if (buttonId.Equals("btn_col2"))
            { lbl_col2.BackColor = colorDialog1.Color; }
            else if (buttonId.Equals("btn_col3"))
            { lbl_col3.BackColor = colorDialog1.Color; }
        }

        private void btn_run_Click(object sender, EventArgs e)
        {
            string space = " ";
            string command = "/C Lab2_OpenGL.exe ";

            //----------------------1
            //command += txt_FirstSentence.Text.TrimEnd();
            command += current.ToString();
            command += space;

            //----------------------2
            //command += txt_Rule1.Text.TrimEnd();
            command += "12";
            command += space;

            //----------------------3
            //command += txt_Rule2.Text.TrimEnd();
            command += "15";
            command += space;

            //----------------------4
            // command += txt_Rule3.Text.TrimEnd();
            command += "16";
            command += space;

            //----------------------5
            //command += txt_Rule4.Text.TrimEnd();
            command += "11";
            command += space;

            //----------------------6
            //command += txt_Rule5.Text.TrimEnd();
            command += "9";
            command += space;

            //----------------------ANGLE ..
            command += txt_Angle.Text.TrimEnd();
            command += space;

            command += txt_Iteration.Text.TrimEnd();
            command += space;

            command += txt_Type.Text.TrimEnd();
            command += space;

            //Assigning Colors (Lable 1)
            command += ColorToRGB(lbl_col1.BackColor.R.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col1.BackColor.G.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col1.BackColor.B.ToString()).TrimEnd();
            command += space;

            //Assigning Colors (Lable 2)
            command += ColorToRGB(lbl_col2.BackColor.R.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col2.BackColor.G.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col2.BackColor.B.ToString()).TrimEnd();
            command += space;

            //Assigning Colors (Lable 3)
            command += ColorToRGB(lbl_col3.BackColor.R.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col3.BackColor.G.ToString()).TrimEnd();
            command += space;

            command += ColorToRGB(lbl_col3.BackColor.B.ToString()).TrimEnd();
            command += space;

            //3D
            if (current > 8)
            {
                if (chk_3d.Checked) { command += "1"; }
                else { command += "0"; }
            }
            else
            {
                command += "0";
            }

            command += space;


            //forest
            command += "0";
            command += space;



            System.Diagnostics.Process process = new System.Diagnostics.Process();
            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
            startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            startInfo.FileName = "cmd.exe";
            //startInfo.Arguments = "/C Lab2_OpenGL.exe F+F+F+F F+F-F-FF+F+F-F F F F F 90 4 0";
            startInfo.Arguments = command;
            process.StartInfo = startInfo;
            process.Start();
        }

        private void btn_remove_Click(object sender, EventArgs e)
        {
            if (lst_final.SelectedIndex == -1)
            {
                MessageBox.Show("Please select an Item first!");
            }
            else
            {
                
                switch (lst_final.SelectedItem.ToString())
                {
                    case "9": { t1.BorderStyle = BorderStyle.None; break; }
                    case "10": { t2.BorderStyle = BorderStyle.None; break; }
                    case "11": { t3.BorderStyle = BorderStyle.None; break; }
                    case "12": { t4.BorderStyle = BorderStyle.None; break; }
                    case "13": { t5.BorderStyle = BorderStyle.None; break; }
                    case "14": { t6.BorderStyle = BorderStyle.None; break; }
                    case "15": { t7.BorderStyle = BorderStyle.None; break; }
                    case "16": { t8.BorderStyle = BorderStyle.None; break; }
                }

                lst_final.Items.Remove(lst_final.SelectedItem);
            }
        }

        private void btn_forest_Click(object sender, EventArgs e)
        {

            //{
                if (lst_final.Items.Count == 0)
                {
                    MessageBox.Show("Please Add at least one tree to the list");
                }
                else
                {
                    string[] tree = new string[] { "0", "0", "0", "0", "0", "0" };
                    for (int i = 0; i < lst_final.Items.Count; i++)
                    {
                        tree[i] = lst_final.Items[i].ToString();
                        //MessageBox.Show(tree[i]);
                    }

                    string space = " ";
                    string command = "/C Lab2_OpenGL.exe ";

                    //----------------------1
                    //command += txt_FirstSentence.Text.TrimEnd();
                    //command += current.ToString();
                    command += tree[0];
                    command += space;

                    //----------------------2
                    //command += txt_Rule1.Text.TrimEnd();
                    command += tree[1];
                    command += space;

                    //----------------------3
                    //command += txt_Rule2.Text.TrimEnd();
                    command += tree[2];
                    command += space;

                    //----------------------4
                    // command += txt_Rule3.Text.TrimEnd();
                    command += tree[3];
                    command += space;

                    //----------------------5
                    //command += txt_Rule4.Text.TrimEnd();
                    command += tree[4];
                    command += space;

                    //----------------------6
                    //command += txt_Rule5.Text.TrimEnd();
                    command += tree[5];
                    command += space;

                    //----------------------ANGLE ..

                    string ANGLE = "";
                    string ITERATION = "";
                    string TYPE = "";

                    switch (tree[0])
                    {
                        case "9":
                            {
                                ANGLE = ("25.7");
                                ITERATION = ("5");
                                TYPE = ("0");
                                break;
                            }
                        case "10":
                            {
                                ANGLE = ("20.7");
                                ITERATION = ("7");
                                TYPE = ("3");
                                break;
                            }
                        case "11":
                            {
                                ANGLE = ("22.5");
                                ITERATION = ("5");
                                TYPE = ("3");
                                break;
                            }
                        case "12":
                            {
                                ANGLE = ("25.7");
                                ITERATION = ("7");
                                TYPE = ("3");
                                break;
                            }
                        case "13":
                            {
                                ANGLE = ("22.5");
                                ITERATION = ("4");
                                TYPE = ("4");
                                break;
                            }
                        case "14":
                            {
                                ANGLE = ("25.7");
                                ITERATION = ("5");
                                TYPE = ("6");
                                break;
                            }
                        case "15":
                            {
                                ANGLE = ("18");
                                ITERATION = ("9");
                                TYPE = ("7");
                                break;
                            }
                        case "16":
                            {
                                ANGLE = ("30");
                                ITERATION = ("5");
                                TYPE = ("8");
                                break;
                            }
                    }

                    command += ANGLE;
                    command += space;

                    command += ITERATION;
                    command += space;

                    command += TYPE;
                    command += space;

                    //Assigning Colors (Lable 1)
                    command += ColorToRGB(lbl_col1.BackColor.R.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col1.BackColor.G.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col1.BackColor.B.ToString()).TrimEnd();
                    command += space;

                    //Assigning Colors (Lable 2)
                    command += ColorToRGB(lbl_col2.BackColor.R.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col2.BackColor.G.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col2.BackColor.B.ToString()).TrimEnd();
                    command += space;

                    //Assigning Colors (Lable 3)
                    command += ColorToRGB(lbl_col3.BackColor.R.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col3.BackColor.G.ToString()).TrimEnd();
                    command += space;

                    command += ColorToRGB(lbl_col3.BackColor.B.ToString()).TrimEnd();
                    command += space;

                    //3D
                    if (chk_3d.Checked) { command += "1"; }
                    else { command += "0"; }

                    command += space;


                    //forest
                    command += "1";
                    command += space;



                    System.Diagnostics.Process process = new System.Diagnostics.Process();
                    System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
                    //startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                    startInfo.FileName = "cmd.exe";
                    //startInfo.Arguments = "/C Lab2_OpenGL.exe F+F+F+F F+F-F-FF+F+F-F F F F F 90 4 0";
                    startInfo.Arguments = command;
                    process.StartInfo = startInfo;
                    process.Start();

                }
            //}
        }

        private void t1_Click(object sender, EventArgs e)
        {
            if (lst_final.Items.Count > 5)
            {
                MessageBox.Show("There are enough trees in final list");
            }
            else
            {
                PictureBox button = (PictureBox)sender;
                string buttonId = button.Name;

                t1.BorderStyle = BorderStyle.None;
                t2.BorderStyle = BorderStyle.None;
                t3.BorderStyle = BorderStyle.None;
                t4.BorderStyle = BorderStyle.None;
                t5.BorderStyle = BorderStyle.None;
                t6.BorderStyle = BorderStyle.None;
                t7.BorderStyle = BorderStyle.None;

                switch (buttonId)
                {
                    case "t1": { lst_final.Items.Add(9); break; }
                    case "t2": { lst_final.Items.Add(10); break; }
                    case "t3": { lst_final.Items.Add(11); break; }
                    case "t4": { lst_final.Items.Add(12); break; }
                    case "t5": { lst_final.Items.Add(13); break; }
                    case "t6": { lst_final.Items.Add(14); break; }
                    case "t7": { lst_final.Items.Add(15); break; }
                    case "t8": { lst_final.Items.Add(16); break; }
                }

                for (int i = 0; i < lst_final.Items.Count; i++)
                {

                    switch (lst_final.Items[i].ToString())
                    {
                        case "9": { t1.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "10": { t2.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "11": { t3.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "12": { t4.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "13": { t5.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "14": { t6.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "15": { t7.BorderStyle = BorderStyle.Fixed3D; break; }
                        case "16": { t8.BorderStyle = BorderStyle.Fixed3D; break; }
                    }
                }
                
            }


        }
    }
}
