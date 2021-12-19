using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using trs.Models;
using System.ComponentModel.DataAnnotations;

namespace trs.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;

    public HomeController(ILogger<HomeController> logger)
    {
        _logger = logger;
    }

    public IActionResult Index()
    {
        /*IList<ActivityModel> newList = new List<ActivityModel>();

        ActivityModel newAct = new ActivityModel();
        newAct.code = "Dev-1";
        newAct.manager = "jan";
        newAct.name = "Development";
        newAct.budget = 200;
        newList.Add(newAct);
        newAct = new ActivityModel();
        newAct.code = "DT-2";
        newAct.manager = "kowal";
        newAct.name = "Data Mining";
        newAct.budget = 300;
        newList.Add(newAct);

        ActivityModel.SaveActivityList(newList);*/

        return View();
    }

    [HttpPost]
    public IActionResult Index(HIndexModel model)
    {
        GDataModel.Gdate = new DateTime(2020, 11, 10);
        GDataModel.Gusername = model.username;

        HActivitiesModel Amodel = new HActivitiesModel();
        Amodel.entries = new List<EntryTableModel>();

        Amodel.date = GDataModel.Gdate.ToString("yyyy-MM-dd");
        Amodel.totalTime = 0;

        //System.Diagnostics.Debug.WriteLine("");

        return RedirectToAction("Activities", Amodel);
    }

    public IActionResult Activities(HActivitiesModel model)
    {
        if (model.date == null || model.date == "")
            model.date = GDataModel.Gdate.ToString("yyyy-MM-dd");
        else
            GDataModel.Gdate = DateTime.Parse(model.date);

        if (model.entries == null)
            model.entries = new List<EntryTableModel>();


        ReportModel report = ReportModel.GetReport(GDataModel.Gusername, GDataModel.Gdate);

        int timeSum = 0;
        for (int i=0; i<report?.entries?.Count(); i++)
        {
            if (report.entries[i].date != GDataModel.Gdate)
                continue;

            EntryTableModel newEntry = new EntryTableModel();
            newEntry.code = report.entries[i].code;
            newEntry.projectName = ActivityModel.GetProjectName(newEntry.code);
            newEntry.time = report.entries[i].time;
            newEntry.date = report.entries[i].date;
            newEntry.description = report.entries[i].description;
            model.entries.Add(newEntry);

            timeSum += newEntry.time;
        }

        model.totalTime = timeSum;

        return View(model);
    }

    public IActionResult DeleteEntry(int id)
    {
        ReportModel report = ReportModel.GetReport(GDataModel.Gusername, GDataModel.Gdate);
        for (int i=0; i<report?.entries?.Count(); i++)
        {
            if (report.entries[i].date != GDataModel.Gdate)
                continue;
            
            id--;
            if (id < 0)
            {
                report.entries.RemoveAt(i);
                ReportModel.SaveReport(report);

                break;
            }
        }

        return RedirectToAction("Activities");
    } 

    public IActionResult EntryDetails(int id)
    {
        EntryDetailsModel model = new EntryDetailsModel();

        ReportModel report = ReportModel.GetReport(GDataModel.Gusername, GDataModel.Gdate);
        for (int i=0; i<report?.entries?.Count(); i++)
        {
            if (report.entries[i].date != GDataModel.Gdate)
                continue;
            
            id--;
            if (id < 0)
            {
                model.entry = report.entries[i];
                model.project = ActivityModel.GetActivity(model.entry.code);

                break;
            }
        }

        return View(model);
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
