using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using trs.Models;

namespace trs.Controllers;

public class HomeController : Controller
{
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

        IList<ActivityModel> aktList = ActivityModel.GetActivityList();

        System.Diagnostics.Debug.WriteLine(aktList[0].code + "\n" + aktList[1].code);

        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
