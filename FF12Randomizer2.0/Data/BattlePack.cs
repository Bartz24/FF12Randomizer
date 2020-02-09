using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12RandomizerVer2
{
    public class BattlePack
    {
        private ByteArray[] sections = new ByteArray[0x48];

        public DataStoreArray<DataStoreEquip> Equipment
        {
            get
            {
                DataStoreArray<DataStoreEquip> dataArray = new DataStoreArray<DataStoreEquip>((int)sections[14].ReadUInt(0x04), 52, 0x20);
                dataArray.LoadData(sections[13]);
                dataArray.AddAccessModifier(i => i >= 4096 ? i - 4096 : i);
                return dataArray;
            }
        }

        public WordPack WordFile
        {
            get
            {
                if (!File.Exists("word.bin"))
                    File.WriteAllBytes("word.bin", sections[38].Data);
                return new WordPack("word.bin");
            }
        }

        public BattlePack(string filePath)
        {
            ByteArray allData = new ByteArray(File.ReadAllBytes(filePath));
            int sectionI = 0;
            for (int i = 0; i < sections.Length; i++)
            {
                int start = (int)allData.ReadUInt((i + 1) * 4);
                int end = (int)allData.ReadUInt((i + 2) * 4);
                if (start == end)
                    continue;                
                sections[sectionI] = new ByteArray(allData.Data.SubArray(start, (end == 0 ? allData.Data.Length : end) - start - 4));
                sectionI++;
            }
        }
    }
}
