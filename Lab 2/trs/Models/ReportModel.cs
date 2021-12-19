using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.ComponentModel.DataAnnotations;

namespace trs.Models;

public class ReportModel
{
    public List<EntryModel> entries { get; set; }
    [JsonIgnore]
    [DataType(DataType.Date)]
    public DateTime date { get; set; }
    [JsonIgnore]
    public string username { get; set; }

    // ---------- public static methods (for accessing data)

    public static ReportModel GetReport(string username, DateTime date)
    {
        string filename = "Data/" + username + "-" + date.Year + "-" + date.Month + ".json";

        if (!File.Exists(filename))//return null in case file doeas not exist
            return null;

        string jsonString = File.ReadAllText(filename);
        ReportModel report = JsonSerializer.Deserialize<ReportModel>(jsonString);
        report.date = date;
        report.username = username;

        return report;
    }

    public static void SaveReport(ReportModel report)
    {
        string filename = "Data/" + report.username + "-" + report.date.Year + "-" + report.date.Month + ".json";

        string jsonString = JsonSerializer.Serialize(report);
        File.WriteAllText(filename, jsonString);
    }

    public static void AddEntry(EntryModel newEntry, string username)
    {
        ReportModel report = GetReport(username, newEntry.date);

        if (report == null)//if report does not exist for current user and date
        {
            report = new ReportModel();
            report.date = newEntry.date;
            report.username = username;
        }

        report.entries.Add(newEntry);
    }

    public static void RemoveEntry(int index)
    {
        //TO DO - implement
    }

    public static void EditEntry(int index, EntryModel newEntry)
    {
        //TO DO - implement
    }
}
