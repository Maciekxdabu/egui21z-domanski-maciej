namespace trs.Models;

public class HIndexModel
{
    public string username { get; set; }
}

public class HActivitiesModel
{
    public string date { get; set; }
    public List<EntryTableModel> entries { get; set; }
    public int totalTime { get; set; }
}

public class EntryDetailsModel
{
    public EntryModel entry { get; set; }

    public ActivityModel project { get; set; }
}