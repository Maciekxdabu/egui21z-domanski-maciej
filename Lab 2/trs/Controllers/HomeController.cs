﻿using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using trs.Models;
using System.ComponentModel.DataAnnotations;

namespace trs.Controllers;

public class HomeController : Controller
{
    //DEBUG ONLY
    public static string username = "jan";
    [DataType(DataType.Date)]
    public static DateTime date = new DateTime(2021, 12, 19);



    private readonly ILogger<HomeController> _logger;

    public HomeController(ILogger<HomeController> logger)
    {
        _logger = logger;
    }

    public IActionResult Index(LectureModel person)
    {
        //TO DO - check if first entry and if YES: ask for login
        
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

        ReportModel report = ReportModel.GetReport(username, date);

        if (report == null)
            return View();

        List<EntryTableModel> entryTable = new List<EntryTableModel>();

        for (int i=0; i<report.entries.Count(); i++)
        {
            //if (report.entries[i].date != date)
                //continue;

            EntryTableModel newEntry = new EntryTableModel();
            newEntry.code = report.entries[i].code;
            newEntry.projectName = ActivityModel.GetProjectName(newEntry.code);
            newEntry.time = report.entries[i].time;
            newEntry.date = report.entries[i].date;
            newEntry.description = report.entries[i].description;
            entryTable.Add(newEntry);
        }

        return View(entryTable);
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
