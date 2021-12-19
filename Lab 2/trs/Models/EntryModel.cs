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

public class EntryTableModel
{
    [Display(Name = "Project Name")]
    public string projectName { get; set; }//used only when displayed in table
    [Display(Name = "Project Code")]
    public string code { get; set; }
    [Display(Name = "Time")]
    public int time { get; set; }
    [Display(Name = "Description")]
    public string description { get; set; }
    [DataType(DataType.Date)]
    public DateTime date { get; set; }
}

public class EntryViewModel
{
    public EntryModel entry { get; set; }
    public List<SelectListItem> projectCodes { get; set; }
}