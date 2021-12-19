Version 0.3.1 - Entry Dialog completed
- Now prints entries table on the main page
- Now it can successfully add entries to the current report (but date still needs fixing)

Version 0.2.2
- Added Cancel button for Entry dialog
- Added AddEntry function and declared RemoveEntry and EditEntry for ReportModel

Version 0.2.1 - start of working on the Entry Dialog
- Added ReportModel with static function to get and save the data
- commented the "Nullable" in trs.csproj in order to get rid of warnings
- EntryController now has two Index methods, one marked with \[HttpPost\] attribute in order to receive and analyze the given data

Version 0.1.4
- Updated Entry View so it now displays approporiate project names (approporiate project code is sent when submitted)

Version 0.1.3
- Added ActivityModel
- Written static functions to read and save activity data from json file (latter only used in development)

Version 0.1.2
- Added Changelog and updated information about last commit
- Updated Views:
	- Home: Index
	- Entry: Index
- Deleted Privacy View and all access to it
- Updated navigation
- Added Entry model and used it in Entry view

Version 0.1.1 - Initial commit
- Created base mvc project
- Made a rough sketch of Home and Entry Controllers Index views