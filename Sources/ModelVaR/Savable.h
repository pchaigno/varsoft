#pragma once

#include "ModelVaR_global.h"

enum SaveStatus {
	UPTODATE, // The two versions are identical.
	MODIFIED, // Version in memory is different from the one in the database.
	ABSENT // Absent from the database.
};

class MODELVARSHARED_EXPORT Savable {
private:
	SaveStatus saveStatus;

public:
	bool isUpToDate() const;
	bool isModified() const;
	bool isAbsent() const;

protected:
	Savable(bool fromDatabase);
	void setStatusToModified();
	void setStatusToUpToDate();
};
