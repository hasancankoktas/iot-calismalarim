using FireSharp;
using FireSharp.Config;
using FireSharp.Interfaces;
using FireSharp.Response;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Firebase
{
    public partial class Form1 : Form
    {
        IFirebaseClient client; 

        IFirebaseConfig config = new FirebaseConfig
        {
            AuthSecret = "4Buo1KUwX39NMZvkK8AcFMLQfj6IDYzaZtZEBGlI",
            BasePath = "https://iot-1-3f804-default-rtdb.firebaseio.com/"
        };

        public Form1()
        {
            InitializeComponent();
        }

        private async void timer1_Tick(object sender, EventArgs e)
        {
            FirebaseResponse response = await client.GetTaskAsync("Sicaklik");
            label1.Text = "Okunan Sıcaklık Değeri:" + response.Body;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            client = new FirebaseClient(config);
            if (client != null)
                MessageBox.Show("Firebase Realtime Database'e bağlandı", "Bağlantı", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            client.Set("TurnOn", float.Parse(textBox1.Text));
        }
    }
}
