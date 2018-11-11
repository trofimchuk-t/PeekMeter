using System.Runtime.InteropServices;

namespace PeekMeterWrapper
{
    public class PeekMeterNative
    {
        [DllImport(@"PeekMeter.dll", EntryPoint = "GetLevel")]
        public static extern float GetLevel();

        [DllImport(@"PeekMeter.dll", EntryPoint = "GetChannelsCount")]
        public static extern int GetChannelsCount();

        [DllImport(@"PeekMeter.dll", EntryPoint = "GetLevels")]
        public static extern bool GetLevels(int channelsCount, float[] levels);
    }
}