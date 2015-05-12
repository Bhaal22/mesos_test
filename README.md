# mesos_test

TODO:
 - read input file for Resources / Jobs
 - make Resources dynamic following a dedicated scenario
 - fix waiting for futures [OK]
 - simpleRunner does not work correctly with resource status
 - need to sync on resource.used attribute [OK]
 - when a Task is finished, it does to set resource as available [OK]


Very simple API for Simulator :
 - template parameter for JobRunner Strategy and Scheduler AssignementStrategy
 - call start method on the Scheduler instance