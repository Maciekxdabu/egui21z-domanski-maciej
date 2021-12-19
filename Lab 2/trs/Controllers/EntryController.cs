using Microsoft.AspNetCore.Mvc;
using System.Text.Encodings.Web;
using trs.Models;

namespace trs.Controllers
{
    public class EntryController : Controller
    {
        public IActionResult Index()
        {
            EntryViewModel newModel = new EntryViewModel();

            newModel.entry = new EntryModel();
            newModel.projectCodes = ActivityModel.GetCodesList();

            return View(newModel);
        }

        [HttpPost]
        public IActionResult Index(EntryViewModel model)//when receiving submitted entry
        {
            model.entry.date = GDataModel.Gdate;
            ReportModel.AddEntry(model.entry);

            return RedirectToAction("Activities", "Home");
        }
    }
}