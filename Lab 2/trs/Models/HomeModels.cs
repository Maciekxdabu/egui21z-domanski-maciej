using System.ComponentModel.DataAnnotations;

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