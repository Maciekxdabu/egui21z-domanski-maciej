using System.ComponentModel.DataAnnotations;

namespace trs.Models;

public class HIndexModel
{
    public string username { get; set; }
}

public class HActivitiesModel
{
    [DataType(DataType.Date)]
    public DateTime date { get; set; }
    public List<EntryTableModel> entries { get; set; }
    public int totalTime { get; set; }
}