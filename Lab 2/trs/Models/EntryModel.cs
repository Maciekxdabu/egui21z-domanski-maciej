using Microsoft.AspNetCore.Mvc.Rendering;

namespace trs.Models;

public class EntryModel
{
    public string? code { get; set; }
    public int? time { get; set; }
    public string? description { get; set; }
}

public class EntryViewModel
{
    public EntryModel? entry { get; set; }
    public List<SelectListItem>? projectCodes { get; set; }
}