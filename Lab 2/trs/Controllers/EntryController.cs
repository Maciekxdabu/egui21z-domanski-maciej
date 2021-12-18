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

        public IActionResult Submit(EntryViewModel model)
        {
            System.Diagnostics.Debug.WriteLine("code: " + model.entry.code + " time: " + model.entry.time + " description: " + model.entry.description);

            return View("Index", model);
        }
    }
}