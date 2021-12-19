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
        public IActionResult Index(EntryViewModel model)
        {
            System.Diagnostics.Debug.WriteLine("code: " + model.entry.code + " time: " + model.entry.time + " description: " + model.entry.description);
            model.projectCodes = ActivityModel.GetCodesList();

            return View(model);
        }
    }
}