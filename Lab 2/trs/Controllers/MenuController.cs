using Microsoft.AspNetCore.Mvc;
using System.Text.Encodings.Web;
using trs.Models;

namespace trs.Controllers
{
    public class MenuController : Controller
    {
        public IActionResult Index()
        {
            MIndexModel model = new MIndexModel();
            model.date = GDataModel.Gdate.ToString("MM-yyyy");
            model.tableEntries = new List<MEntry>();

            ReportModel report = ReportModel.GetReport(GDataModel.Gusername, GDataModel.Gdate);
            for (int i=0; i<report?.entries?.Count(); i++)
            {
                bool found = false;
                for (int j=0; j<model.tableEntries.Count(); j++)
                {
                    if (model.tableEntries[j].projectCode == report.entries[i].code)
                    {
                        found = true;

                        model.tableEntries[j].timeSpent += report.entries[i].time;
                    }
                }

                if (!found)
                {
                    MEntry newEntry = new MEntry();
                    newEntry.projectCode = report.entries[i].code;
                    newEntry.projectName = ActivityModel.GetProjectName(report.entries[i].code);
                    newEntry.timeSpent = report.entries[i].time;
                    model.tableEntries.Add(newEntry);
                }
            }

            return View(model);
        }
    }
}