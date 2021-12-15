using Microsoft.AspNetCore.Mvc;
using System.Text.Encodings.Web;

namespace trs.Controllers
{
    public class EntryController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}