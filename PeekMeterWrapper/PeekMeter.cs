namespace PeekMeterWrapper
{
    public class PeekMeter : IPeekMeter
    {
        public const int MaxChannelsCount = 8;

        private readonly float[] levels = new float[MaxChannelsCount];

        public float GelLevel()
        {
            return PeekMeterNative.GetLevel();
        }

        public int GetChannelsCount()
        {
            return PeekMeterNative.GetChannelsCount();
        }

        public float[] GetLevels()
        {
            int channelsCount = PeekMeterNative.GetChannelsCount();
            PeekMeterNative.GetLevels(channelsCount, levels);

            return levels;
        }
    }
}