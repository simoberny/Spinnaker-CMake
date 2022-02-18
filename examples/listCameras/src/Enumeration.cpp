/**
 *	@example Enumeration.cpp
 *
 *  @brief Enumeration.cpp shows how to enumerate interfaces and cameras.
 *	Knowing this is mandatory for doing anything with the Spinnaker SDK, and is
 *	therefore the best place to start learning how to use the SDK.
 *
 *	This example introduces the preparation, use, and cleanup of the system
 *	object, interface and camera lists, interfaces, and cameras. It also touches
 *	on retrieving both nodes from nodemaps and information from nodes.
 *
 *	Once comfortable with enumeration, we suggest checking out the Acquisition,
 *	ExceptionHandling, or NodeMapInfo examples. Acquisition demonstrates using
 *	a camera to acquire images, ExceptionHandling explores the use of standard
 *	and Spinnaker exceptions, and NodeMapInfo demonstrates retrieving
 *	information from various node types.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function queries an interface for its cameras and then prints out device
// information.
int QueryInterface(InterfacePtr pInterface)
{
    int result = 0;

    try
    {
        INodeMap& nodeMapInterface = pInterface->GetTLNodeMap();

        // Get interface name
        CStringPtr ptrInterfaceDisplayName = nodeMapInterface.GetNode("InterfaceDisplayName");

        if (IsAvailable(ptrInterfaceDisplayName) && IsReadable(ptrInterfaceDisplayName))
        {
            gcstring interfaceDisplayName = ptrInterfaceDisplayName->GetValue();
            cout << interfaceDisplayName << endl;
        }
        else
        {
            cout << "Interface display name not readable" << endl;
        }

        pInterface->UpdateCameras();
        CameraList camList = pInterface->GetCameras();

        // Retrieve number of cameras
        unsigned int numCameras = camList.GetSize();

        // Return if no cameras detected
        if (numCameras == 0)
        {
            cout << "\tNo devices detected." << endl << endl;
            return result;
        }

        // Print device vendor and model name for each camera on the interface
        for (unsigned int i = 0; i < numCameras; i++)
        {

            CameraPtr pCam = camList.GetByIndex(i);

            // Retrieve TL device nodemap; please see NodeMapInfo example for
            // additional comments on transport layer nodemaps
            INodeMap& nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

            cout << "\tDevice " << i << " ";
            
            CStringPtr ptrDeviceVendorName = nodeMapTLDevice.GetNode("DeviceVendorName");

            if (IsAvailable(ptrDeviceVendorName) && IsReadable(ptrDeviceVendorName))
            {
                gcstring deviceVendorName = ptrDeviceVendorName->ToString();

                cout << deviceVendorName << " ";
            }

            CStringPtr ptrDeviceModelName = nodeMapTLDevice.GetNode("DeviceModelName");

            if (IsAvailable(ptrDeviceModelName) && IsReadable(ptrDeviceModelName))
            {
                gcstring deviceModelName = ptrDeviceModelName->ToString();

                cout << deviceModelName << endl << endl;
            }
        }

        camList.Clear();
    }
    catch (Spinnaker::Exception& e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

int main(int /*argc*/, char** /*argv*/)
{
    int result = 0;

    SystemPtr system = System::GetInstance();

    // Print out current library version
    const LibraryVersion spinnakerLibraryVersion = system->GetLibraryVersion();
    cout << "Spinnaker library version: " << spinnakerLibraryVersion.major << "." << spinnakerLibraryVersion.minor
         << "." << spinnakerLibraryVersion.type << "." << spinnakerLibraryVersion.build << endl
         << endl;

    InterfaceList interfaceList = system->GetInterfaces();

    unsigned int numInterfaces = interfaceList.GetSize();
    cout << "Number of interfaces detected: " << numInterfaces << endl << endl;

    CameraList camList = system->GetCameras();

    unsigned int numCameras = camList.GetSize();
    cout << "Number of cameras detected: " << numCameras << endl << endl;

    // If no camera
    if (numCameras == 0 || numInterfaces == 0)
    {
        // Clear camera list before releasing system
        camList.Clear();

        // Clear interface list before releasing system
        interfaceList.Clear();

        // Release system
        system->ReleaseInstance();

        cout << "Not enough cameras!" << endl;
        cout << "Done! Press Enter to exit..." << endl;
        getchar();

        return -1;
    }

    cout << endl << "*** QUERYING INTERFACES ***" << endl << endl;

    InterfacePtr interfacePtr = nullptr;

    for (unsigned int i = 0; i < numInterfaces; i++)
    {
        // Select interface
        interfacePtr = interfaceList.GetByIndex(i);

        // Query interface
        result = result | QueryInterface(interfacePtr);
    }


    interfacePtr = nullptr;
    camList.Clear();
    interfaceList.Clear();

    system->ReleaseInstance();

    cout << endl << "Done! Press Enter to exit..." << endl;
    getchar();

    return result;
}
