using System.IO;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace trs.Models;

public class ActivityModel
{
    public string code { get; set; }
    public string manager { get; set; }
    public string name { get; set; }
    public int budget { get; set; }

    // ---------- public static methods

    public static IList<ActivityModel> GetActivityList()
    {
        string jsonString = File.ReadAllText("Data/activity.json");
        IList<ActivityModel> newList = JsonSerializer.Deserialize<IList<ActivityModel>>(jsonString);

        return newList;
    }

    public static List<SelectListItem> GetCodesList()
    {
        IList<ActivityModel> newList = GetActivityList();
        List<SelectListItem> codeList = new List<SelectListItem>();

        for (int i=0; i<newList.Count; i++)
        {
            SelectListItem newItem = new SelectListItem();

            newItem.Text = newList[i].name;
            newItem.Value = newList[i].code;

            codeList.Add(newItem);
        }

        return codeList;
    }

    public static string GetProjectName(string code)
    {
        IList<ActivityModel> aktList = GetActivityList();

        foreach (var akt in aktList)
        {
            if (akt.code == code)
                return akt.name;
        }

        return "";
    }

    public static void SaveActivityList(IList<ActivityModel> newList)
    {
        string jsonString = JsonSerializer.Serialize(newList);
        File.WriteAllText("Data/activity.json", jsonString);
    }
}