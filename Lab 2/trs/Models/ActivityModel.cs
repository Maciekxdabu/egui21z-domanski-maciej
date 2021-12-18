using System.IO;
using System.Text.Json;

namespace trs.Models;

public class ActivityModel
{
    public string? code { get; set; }
    public string? manager { get; set; }
    public string? name { get; set; }
    public int? budget { get; set; }

    public static IList<ActivityModel> GetActivityList()
    {
        IList<ActivityModel> newList;

        string jsonString = File.ReadAllText("Data/activity.json");
        newList = JsonSerializer.Deserialize<IList<ActivityModel>>(jsonString);

        return newList;
    }

    public static void SaveActivityList(IList<ActivityModel> newList)
    {
        string jsonString = JsonSerializer.Serialize(newList);
        File.WriteAllText("Data/activity.json", jsonString);
    }
}