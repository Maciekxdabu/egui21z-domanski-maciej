using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations;

namespace trs.Models;

public class EntryModel
{
    public string code { get; set; }
    public int time { get; set; }
    public string description { get; set; }
    [DataType(DataType.Date)]
    public DateTime date { get; set; }
}

public class EntryViewModel
{
    public EntryModel entry { get; set; }
    public List<SelectListItem> projectCodes { get; set; }
}