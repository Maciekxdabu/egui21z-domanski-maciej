using System.ComponentModel.DataAnnotations;

namespace trs.Models;

public class GDataModel
{
    public static string Gusername;//global username variable
    [DataType(DataType.Date)]
    public static DateTime Gdate;//global date variable
}