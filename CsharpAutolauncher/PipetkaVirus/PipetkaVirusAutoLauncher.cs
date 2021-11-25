using Microsoft.Win32;
using Microsoft.CSharp;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Management;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Reflection;
using System.Media;
using System.Security.AccessControl;
using System.CodeDom.Compiler;
using System.Net;
using System.Net.Security;
using System.Speech.Synthesis;

namespace PipetkaVirusAutolauncher
{
    public partial class PipetkaVirusAutoLauncher : Form
    {
        public PipetkaVirusAutoLauncher()
        {
            InitializeComponent();
            Directory.CreateDirectory(@"C:\Temp\PipetkaVirus");
            Directory.SetCreationTime(@"C:\Temp\PipetkaVirus", DateTime.Now);
            Directory.SetCurrentDirectory(@"C:\Temp\PipetkaVirus");
            Cursor.Hide();
            if (MessageBox.Show("Do you want to Run Pipetka Virus?" + Environment.NewLine + "This is Very Dangerous", "PipetkaVirus", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1) == DialogResult.Yes)
            {
                Process.Start(@"C:\Temp\PipetkaVirus\Pipetka.exe");
                Environment.Exit(0);
            }
            Environment.Exit(7530);
        }
}   }
