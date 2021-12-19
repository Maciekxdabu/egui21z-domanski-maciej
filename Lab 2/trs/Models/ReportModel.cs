using System.IO;
using System.Text.Json;
using System.ComponentModel.DataAnnotations;

namespace trs.Models;

public class ReportModel
{
    public List<EntryModel> entries { get; set; }
    [DataType(DataType.Date)]
    public DateTime date { get; set; }
    public string username { get; set; }

    // ---------- public static methods

    public static ReportModel GetReport(string username, DateTime date)
    {
        string filename = "Data/" + username + "-" + date.Year + "-" + date.Month + ".json";

        if (!File.Exists(filename))//return null in case file doeas not exist
            return null;

        string jsonString = File.ReadAllText(filename);
        ReportModel report = JsonSerializer.Deserialize<ReportModel>(jsonString);

        return report;
    }

    public static void SaveReport(ReportModel report)
    {
        string filename = "Data/" + report.username + "-" + report.date.Year + "-" + report.date.Month + ".json";

        string jsonString = JsonSerializer.Serialize(report);
        File.WriteAllText(filename, jsonString);
    }
}
