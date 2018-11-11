namespace PeekMeterWrapper
{
    public interface IPeekMeter
    {
        float GelLevel();

        float[] GetLevels();

        int GetChannelsCount();
    }
}