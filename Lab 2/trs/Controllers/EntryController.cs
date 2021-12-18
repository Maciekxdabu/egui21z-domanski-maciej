using Microsoft.AspNetCore.Mvc;
using System.Text.Encodings.Web;
using trs.Models;

namespace trs.Controllers
{
    public class EntryController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Index(EntryModel entry)
        {
            System.Diagnostics.Debug.WriteLine("time: " + entry.time + " description: " + entry.description);

            return View();
        }
    }
}