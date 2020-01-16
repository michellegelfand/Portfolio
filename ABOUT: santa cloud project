"Santa Cloud" is an organisational NAS developed in order to store
data in the local network of an organisation, a storage "cloud".

------------------------------------------------------------------
Featured here are 3 versions of the project in different cycles of its' developement. In every version folder there is a "version notes" file, describing the updates from the previous version.

In the "includes" folder are the header files, these feature descriptions of the role and implementation of each module.

------------------------------------------------------------------
HOW DOES IT WORK?

Users on the network access a shared folder in which they store and withdraw files from ("drag and drop").

our MASTER (main server computer) uses an NBD (network block device)
to draw the saved data from kernel space to user space.

The master then strips and stores the file into slaves (end points in the network, any device that has network access and a storage device (IOT) ), using the RAID 0+1 implementation- the data is both stripped into segments for simultanious writing to several slaves at once for effeciency, and also backed up for reliability).


